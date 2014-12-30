#ifndef FERTILIZER_H
#define FERTILIZER_H

#include <QVector>
#include <QVector3D>
#include <QtMath>
#include <QHash>

#include "gardener.h"

class Bud
{
public:
    Bud(QVector3D);

    QVector3D position;
    QVector3D normal;
    float strength;
    int children;
    QVector<QVector3D> nutrients;
};

inline bool operator==(const Bud &e1, const Bud &e2)
{
    return e1.position == e2.position
           && e1.normal == e2.normal
            && e1.strength == e2.strength;
}

inline uint qHash(const Bud &key, uint seed)
{
    return qHash(key.position.x(), seed) ^ qHash(key.position.y(), seed) ^ qHash(key.position.z(), seed) ^
           qHash(key.normal.x(), seed) ^ qHash(key.normal.y(), seed) ^ qHash(key.normal.z(), seed) ^
           qHash(key.strength, seed);
}

class Seed
{
public:
    Seed();
    Seed(QVector3D position);

    QVector3D position;
    QVector<Bud*> buds;      // nodes on the plant paths, potential branches
};

class Fertilizer
{
public:
    Fertilizer();

    float getStrength(QVector3D position); // how much plant is here
    virtual void grow() = 0;

    void draw();

    void setup(Gardener* gardener);

    virtual void update() = 0;

    int numberOfNutrients;
    float nutrientRadius;
    float budStepSize;
    bool drawNutrients;
    bool drawSeeds;
    float budStrengthMultiplier;

protected:
    QVector<Seed*> seeds;     // start growing
    QVector<QVector3D> nutrients; // hmm om nom nom
    Gardener* gardener;

    virtual float compute(QVector3D position) = 0;
};

#endif // FERTILIZER_H
