#include "potatofertilizer.h"

PotatoFertilizer::PotatoFertilizer()
{
    seeds.append(QVector3D(0.0f, 0.0f, 0.0f));
    this->numberOfNutrients = 100;
    this->randomSeed = 12345;
}

void PotatoFertilizer::grow()
{
    qsrand(this->randomSeed);

    for (int n = 0; n < this->numberOfNutrients; n++) {
        bool hasPosition = false;

    }

}



//nutrients.append(QVector3D(1.0f, 1.0f, 1.0f));
//nutrients.append(QVector3D(2.0f, 2.0f, 2.0f));

float PotatoFertilizer::compute(QVector3D position)
{
    float fResult = 0.0f;
    float fDx, fDy, fDz;

    fDx = fX - this->sSourcePoint[0].x();
    fDy = fY - this->sSourcePoint[0].y();
    fDz = fZ - this->sSourcePoint[0].z();
    fResult += 0.5f/(fDx*fDx + fDy*fDy + fDz*fDz);

    fDx = fX - this->sSourcePoint[1].x();
    fDy = fY - this->sSourcePoint[1].y();
    fDz = fZ - this->sSourcePoint[1].z();
    fResult += 1.0f/(fDx*fDx + fDy*fDy + fDz*fDz);

    fDx = fX - this->sSourcePoint[2].x();
    fDy = fY - this->sSourcePoint[2].y();
    fDz = fZ - this->sSourcePoint[2].z();
    fResult += 1.5f/(fDx*fDx + fDy*fDy + fDz*fDz);

    return fResult;
}
