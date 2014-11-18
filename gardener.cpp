#include "gardener.h"

Gardener::Gardener(float width, float height, float depth)
{
    this->boundingBox = QCube(-width/2.0f, -height/2.0f, -depth/2.0f,
                              width/2.0f, height/2.0f, depth/2.0f);
}

void Gardener::draw()
{

}

bool Gardener::isInside(QVector3D position)
{
    return this->boundingBox.contains(position);
}

QVector3D Gardener::getRandomPointInside(int randomSeed)
{
    QVector3D result;

    qsrand(randomSeed);

    auto validPoint = false;
    auto boundingDimensions = this->boundingBox.size();
    while (!validPoint) {
        result = QVector3D(qrand()/RAND_MAX * boundingDimensions.x(),
                           qrand()/RAND_MAX * boundingDimensions.y(),
                           qrand()/RAND_MAX * boundingDimensions.z());
        validPoint = this->isInside(result);
    }

    return result;
}
