#ifndef GARDENER_H
#define GARDENER_H

#include <QVector3D>

class Gardener
{
public:
    Gardener();

    void draw();

    bool isInside(QVector3D position);

    //QRectF boundingBox;

    QVector3D getRandomPointInside();
};

#endif // GARDENER_H
