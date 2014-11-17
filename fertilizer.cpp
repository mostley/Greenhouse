#include "fertilizer.h"

Fertilizer::Fertilizer()
{
}

float Fertilizer::getStrength(QVector3D position)
{
    if (!this->gardener->isInside(position)) {
        return 0.0f;
    }

    this->compute(position);
}

void Fertilizer::setup(Gardener *gardener)
{
    this->gardener = gardener;
}

