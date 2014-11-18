#include "fertilizer.h"

Fertilizer::Fertilizer()
{
}

float Fertilizer::getStrength(QVector3D position)
{
    if (this->gardener == NULL || !this->gardener->isInside(position)) {
        return 0.0f;
    }

    return this->compute(position);
}

void Fertilizer::setup(Gardener *gardener)
{
    this->gardener = gardener;
}

