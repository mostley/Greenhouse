#include "gardener.h"

Gardener::Gardener(float width, float height, float depth)
{
    this->boundingBox = QCube(-width/2.0f, -height/2.0f, -depth/2.0f,
                              width/2.0f, height/2.0f, depth/2.0f);
    this->randomSeed = 12345;
}

void Gardener::draw()
{

}

void Gardener::init()
{
    qsrand(this->randomSeed);
}

bool Gardener::isInside(QVector3D position)
{
    return this->boundingBox.contains(position);
}

QVector3D Gardener::getRandomPointInside()
{
    QVector3D result;

    auto validPoint = false;
    auto boundingDimensions = this->boundingBox.size();
    while (!validPoint) {
        result = QVector3D((float)qrand()/RAND_MAX * boundingDimensions.x(),
                           (float)qrand()/RAND_MAX * boundingDimensions.y(),
                           (float)qrand()/RAND_MAX * boundingDimensions.z());
        validPoint = this->isInside(result);
    }

    return result;
}
