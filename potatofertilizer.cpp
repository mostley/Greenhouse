#include "potatofertilizer.h"

#include <QtDebug>

PotatoFertilizer::PotatoFertilizer()
{
    seeds.append(QVector3D(0.0f, 0.0f, 0.0f));

    auto b = Bud();
    b.position = QVector3D(0.5,0.5,0.5);
    b.normal = QVector3D(1.0f, 0.0f, 0.0f);
    b.strength = 1.0f;
    //this->buds.append(b);
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

    return;

    while (this->nutrients.size() > 0) {
        for (int n = 0; n < this->seeds.size(); n++) {
            auto seed = this->seeds[n];

            auto deadNutrients = new QVector<QVector3D>();
            for (int i = 0; i < this->numberOfNutrients; i++) {
                auto nutrient = this->nutrients[i];

                if (seed.buds.size() == 0) {
                    auto direction = (seed.position - nutrient).normalized();

                } else {
                    for (int j=0; j<seed.buds.size(); j++) {
                        auto bud = seed.buds[j];

                        auto direction = (bud.position - nutrient).normalized();
                        auto dotProduct = QVector3D::dotProduct(direction, bud.normal);
                        auto angle = qAcos(dotProduct / (direction.length() * bud.normal.length()));
                        if (angle < 45.0f)
                        {
                            auto newBud = Bud();
                            newBud.position = bud.position + direction * this->budStepSize;
                            newBud.normal = direction;
                            newBud.strength = bud.strength;
                            seed.buds.append(newBud);

                            if ((newBud.position - nutrient).length() < this->nutrientRadius) {
                                deadNutrients->append(nutrient);
                            }

                            break;
                        }
                    }
                }
            }

            //remove dead nutrients
            for (int i = 0; i < deadNutrients->size(); i++) {
                auto index = this->nutrients.indexOf(deadNutrients->at(i));
                this->nutrients.remove(index);
            }
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
            auto strength = bud.strength; // e.g. 0.5 - 1.5

            fDx = position.x() - sourcePosition.x();
            fDy = position.y() - sourcePosition.y();
            fDz = position.z() - sourcePosition.z();
            fResult += strength/(fDx*fDx + fDy*fDy + fDz*fDz);
        }
    }

    return fResult;
}
