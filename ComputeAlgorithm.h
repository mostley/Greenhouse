#ifndef COMPUTEALGORITHM_H
#define COMPUTEALGORITHM_H

class ParameterData
{
public:
    ParameterData(QString name, QString value) {
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
