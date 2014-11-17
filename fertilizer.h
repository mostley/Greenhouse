#ifndef FERTILIZER_H
#define FERTILIZER_H

#include <QVector3D>

#include "gardener.h"

class Fertilizer
{
public:
    Fertilizer();

    float getStrength(QVector3D position); // how much plant is here
    virtual void grow() = 0;

    void setup(Gardener* gardener);

protected:
    virtual float compute(QVector3D position) = 0;


private:
    Gardener* gardener;
};

#endif // FERTILIZER_H
