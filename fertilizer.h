#ifndef FERTILIZER_H
#define FERTILIZER_H

#include <QVector>
#include <QVector3D>
#include <QtMath>

#include "gardener.h"

struct Bud
{
    QVector3D position;
    QVector3D normal;
    float strength;
};

class Seed
{
public:
    Seed();
    Seed(QVector3D position);

    QVector3D position;
    QVector<Bud> buds;      // nodes on the plant paths, potential branches
};

class Fertilizer
{
public:
    Fertilizer();

    float getStrength(QVector3D position); // how much plant is here
    virtual void grow() = 0;

    void draw();

    void setup(Gardener* gardener);

    int numberOfNutrients;
    float nutrientRadius;
    float budStepSize;
    bool drawNutrients;
    bool drawSeeds;

protected:
    QVector<Seed> seeds;     // start growing
    QVector<QVector3D> nutrients; // hmm om nom nom
    Gardener* gardener;

    virtual float compute(QVector3D position) = 0;
};

#endif // FERTILIZER_H
