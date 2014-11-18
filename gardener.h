#ifndef GARDENER_H
#define GARDENER_H

#include <QVector3D>

#include "qcube.h"

class Gardener
{
public:
    Gardener(float width, float height, float depth);

    void draw();

    bool isInside(QVector3D position);

    QVector3D getRandomPointInside();

    void init();

    int randomSeed;

private:
    QCube boundingBox;
};

#endif // GARDENER_H
