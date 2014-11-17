#ifndef POTATOFERTILIZER_H
#define POTATOFERTILIZER_H

#include <QVector>
#include <QVector3D>

#include "fertilizer.h"

class PotatoFertilizer : public Fertilizer
{
public:
    PotatoFertilizer();

    void grow();

    int numberOfNutrients;
    int randomSeed;

protected:
    float compute(QVector3D position);

private:
    QVector<QVector3D> seeds;     // start growing
    QVector<QVector3D> nutrients; // hmm om nom nom
    QVector<QVector3D> buds;      // nodes on the plant paths, potential branches

};

#endif // POTATOFERTILIZER_H
