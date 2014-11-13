#ifndef COMPUTEALGORITHM_H
#define COMPUTEALGORITHM_H

#include <QString>
#include "Blob.h"

class ParameterData
{
public:
    ParameterData(QString name, float value) {
        this->name = name;
        this->value = value;
    }

    QString name;
    float value;
};

class ContainerEvaluator
{
public:
    ContainerEvaluator();
    bool Contained(QVector3D position);
};

class ComputeAlgorithm
{
public:
    void SetContainer(ContainerEvaluator containerEvaluator);
    QVector<ParameterData> GetParameters();
    void SetParameters(QVector<ParameterData> parameterData);
    QVector<Blob> Calculate();
};

#endif // COMPUTEALGORITHM_H
