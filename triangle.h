#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QVector3D>

class Triangle
{
public:
    Triangle();

    QVector3D v1;
    QVector3D v2;
    QVector3D v3;
    QVector3D normal;
};

#endif // TRIANGLE_H
