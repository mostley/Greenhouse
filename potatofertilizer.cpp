#include "potatofertilizer.h"

#include <QtDebug>

PotatoFertilizer::PotatoFertilizer()
{
    this->seeds.append(new Seed(QVector3D(0.0f, 0.0f, 0.0f)));
}

PotatoFertilizer::~PotatoFertilizer()
{
    for (int n = 0; n < this->seeds.size(); n++) {
        delete this->seeds[n];
    }
}

void PotatoFertilizer::grow()
{
    this->nutrients.clear();

    for (int n = 0; n < this->numberOfNutrients; n++) {
        auto nutrientPosition = this->gardener->getRandomPointInside();
        this->nutrients.append(nutrientPosition);
    }

    for (int n = 0; n < this->seeds.size(); n++) {
        for (int i = 0; i < this->seeds[n]->buds.size(); i++) {
            delete this->seeds[n]->buds[i];
        }
        this->seeds[n]->buds.clear();
    }
}

void PotatoFertilizer::update()
{
    if (this->nutrients.size() <= 0) {
        return;
    }

    for (int n = 0; n < this->seeds.size(); n++) {
        Seed* seed = this->seeds[n];

        auto connected_buds = QVector<Bud*>();

        Bud* seedBud = new Bud(seed->position);
        if (seed->buds.size() == 0) {
            connected_buds.append(seedBud);
        }

        for (int i = 0; i < this->nutrients.size(); i++) {
            auto nutrient = this->nutrients[i];

            if (seed->buds.size() == 0) {
                //TODO ask gardener if possible (wall in between)
                seedBud->nutrients.append(nutrient);
            } else {
                for (int j=0; j<seed->buds.size(); j++) {
                    Bud* bud = seed->buds[j];

                    if (bud->children > 0) {
                        continue;
                    }

                    if (!connected_buds.contains(bud)) {
                        connected_buds.append(bud);
                    }

                    auto direction = (bud->position - nutrient).normalized();
                    auto dotProduct = QVector3D::dotProduct(direction, bud->normal);
                    auto angle = qAcos(dotProduct / (direction.length() * bud->normal.length()));
                    if (angle < 45.0f)
                    {
                        bud->nutrients.append(nutrient);

                        break;
                    }
                }
            }
        }

        auto deadNutrients = QVector<QVector3D>();
        for (int i=0; i<connected_buds.size(); i++) {
            auto bud = connected_buds[i];

            QVector<QVector3D> listOfNutrients = bud->nutrients;

            if (listOfNutrients.size() == 0) {
                continue;
            }

            auto direction = QVector3D(0,0,0);
            for (int j=0; j<listOfNutrients.size(); j++) {
                direction += listOfNutrients[j];
            }
            direction.normalize();

            auto newBud = new Bud(bud->position + direction * this->budStepSize);
            newBud->normal = direction;
            newBud->strength = bud->strength;
            seed->buds.append(newBud);
            bud->children += 1;

            for (int j=0; j<listOfNutrients.size(); j++) {
                auto nutrient = listOfNutrients[j];
                if ((newBud->position - nutrient).length() < this->nutrientRadius) {
                    deadNutrients.append(nutrient); // consume the nutrient
                }
            }
        }

        //remove dead nutrients (perhaps do it after each seed had a chance to consume it)
        for (int i = 0; i < deadNutrients.size(); i++) {
            auto index = this->nutrients.indexOf(deadNutrients.at(i));
            this->nutrients.remove(index);
        }

        delete seedBud;
    }
}

float PotatoFertilizer::compute(QVector3D position)
{
    float fResult = 0.0f;
    float fDx, fDy, fDz;

    for (int n = 0; n < this->seeds.size(); n++) {
        auto seed = this->seeds[n];

        for (int i=0; i<seed->buds.size(); i++) {
            auto bud = seed->buds[i];
            auto sourcePosition = bud->position;
            auto strength = bud->strength * 0.1f;//this->budStrengthMultiplier; // e.g. 0.5 - 1.5

            fDx = position.x() - sourcePosition.x();
            fDy = position.y() - sourcePosition.y();
            fDz = position.z() - sourcePosition.z();
            fResult += strength/(fDx*fDx + fDy*fDy + fDz*fDz);
        }
    }

    return fResult;
}
