#ifndef FERTILIZER_H
#define FERTILIZER_H

#include <QVector>
#include <QVector3D>

#include "gardener.h"

struct Bud
{
    QVector3D position;
    float strength;
};

class Fertilizer
{
public:
    Fertilizer();

    float getStrength(QVector3D position); // how much plant is here
    virtual void grow() = 0;

    void setup(Gardener* gardener);

    int numberOfNutrients;
    int randomSeed;

protected:
    QVector<QVector3D> seeds;     // start growing
    QVector<QVector3D> nutrients; // hmm om nom nom
    QVector<Bud> buds;      // nodes on the plant paths, potential branches
    Gardener* gardener;

    virtual float compute(QVector3D position) = 0;
};

#endif // FERTILIZER_H
