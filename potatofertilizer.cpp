#include "potatofertilizer.h"

PotatoFertilizer::PotatoFertilizer()
{
    seeds.append(QVector3D(0.0f, 0.0f, 0.0f));
    this->numberOfNutrients = 100;
    this->randomSeed = 12345;

    auto b = Bud();
    b.position = QVector3D(0.5,0.5,0.5);
    b.strength = 1.0f;
    this->buds.append(b);
}

void PotatoFertilizer::grow()
{
    for (int n = 0; n < this->numberOfNutrients; n++) {
        auto nutrientPosition = this->gardener->getRandomPointInside(this->randomSeed);
        this->nutrients.append(nutrientPosition);
    }

    //TODO grow
}

float PotatoFertilizer::compute(QVector3D position)
{
    float fResult = 0.0f;
    float fDx, fDy, fDz;

    for (int i=0; i<this->buds.size(); i++) {
        auto sourcePosition = this->buds[i].position;
        auto strength = this->buds[i].strength; // e.g. 0.5 - 1.5

        fDx = position.x() - sourcePosition.x();
        fDy = position.y() - sourcePosition.y();
        fDz = position.z() - sourcePosition.z();
        fResult += strength/(fDx*fDx + fDy*fDy + fDz*fDz);
    }

    return fResult;
}
