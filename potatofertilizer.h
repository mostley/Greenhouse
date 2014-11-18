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

protected:
    float compute(QVector3D position);

};

#endif // POTATOFERTILIZER_H
