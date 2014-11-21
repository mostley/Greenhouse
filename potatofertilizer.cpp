#include "potatofertilizer.h"

#include <QtDebug>

PotatoFertilizer::PotatoFertilizer()
{
    seeds.append(QVector3D(0.0f, 0.0f, 0.0f));
}

void PotatoFertilizer::grow()
{
    this->nutrients.clear();

    for (int n = 0; n < this->numberOfNutrients; n++) {
        auto nutrientPosition = this->gardener->getRandomPointInside();
        this->nutrients.append(nutrientPosition);
    }

    for (int n = 0; n < this->seeds.size(); n++) {
        this->seeds[n].buds.clear();
    }
}

void PotatoFertilizer::update()
{
    if (this->nutrients.size() <= 0) {
        return;
    }

    for (int n = 0; n < this->seeds.size(); n++) {
        auto seed = &(this->seeds[n]);

        auto connections = QHash<Bud*, QVector<QVector3D>>();
        auto seedBud = Bud();
        seedBud.position = seed->position;
        seedBud.normal = QVector3D(0,0,0);
        seedBud.strength = 1.0;
        if (seed->buds.size() == 0) {
            connections.insert(&seedBud, QVector<QVector3D>());
        }

        for (int i = 0; i < this->nutrients.size(); i++) {
            auto nutrient = this->nutrients[i];

            if (seed->buds.size() == 0) {
                //TODO ask gardener if possible (wall in between)
                connections[&seedBud].append(nutrient);
            } else {
                for (int j=0; j<seed->buds.size(); j++) {
                    auto bud = &(seed->buds[j]);

                    if (bud->children > 0) {
                        continue;
                    }

                    if (!connections.contains(bud)) {
                        connections.insert(bud, QVector<QVector3D>());
                    }

                    auto direction = (bud->position - nutrient).normalized();
                    auto dotProduct = QVector3D::dotProduct(direction, bud->normal);
                    auto angle = qAcos(dotProduct / (direction.length() * bud->normal.length()));
                    if (angle < 45.0f)
                    {
                        connections[bud].append(nutrient);

                        break;
                    }
                }
            }
        }

        auto deadNutrients = QVector<QVector3D>();
        for (int i=0; i<connections.keys().size(); i++) {
            auto bud = connections.keys()[i];
            auto listOfNutrients = connections[bud];

            auto direction = QVector3D(0,0,0);
            for (int j=0; j<listOfNutrients.size(); j++) {
                direction += listOfNutrients[j];
            }
            direction.normalize();

            auto newBud = Bud();
            newBud.position = bud->position + direction * this->budStepSize;
            newBud.normal = direction;
            newBud.strength = bud->strength;
            seed->buds.append(newBud);
            bud->children += 1;

            for (int j=0; j<listOfNutrients.size(); j++) {
                auto nutrient = listOfNutrients[j];
                if ((newBud.position - nutrient).length() < this->nutrientRadius) {
                    deadNutrients.append(nutrient); // consume the nutrient
                }
            }
        }

        //remove dead nutrients (perhaps do it after each seed had a chance to consume it)
        for (int i = 0; i < deadNutrients.size(); i++) {
            auto index = this->nutrients.indexOf(deadNutrients.at(i));
            this->nutrients.remove(index);
        }
    }
}

float PotatoFertilizer::compute(QVector3D position)
{
    float fResult = 0.0f;
    float fDx, fDy, fDz;

    for (int n = 0; n < this->seeds.size(); n++) {
        for (int i=0; i<this->seeds[n].buds.size(); i++) {
            auto bud = this->seeds[n].buds[i];
            auto sourcePosition = bud.position;
            auto strength = bud.strength * 0.1f;//this->budStrengthMultiplier; // e.g. 0.5 - 1.5

            fDx = position.x() - sourcePosition.x();
            fDy = position.y() - sourcePosition.y();
            fDz = position.z() - sourcePosition.z();
            fResult += strength/(fDx*fDx + fDy*fDy + fDz*fDz);
        }
    }

    return fResult;
}
