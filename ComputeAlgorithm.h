#ifndef COMPUTEALGORITHM_H
#define COMPUTEALGORITHM_H

class ParameterData
{
public:
    QString name;
    float value;
};

class ComputeAlgorithm
{
public:
    void SetContainer(bool (*containerCallback)(QVector3D));
    QVector<ParameterData> GetParameters();
    void SetParameters(QVector<ParameterData> parameterData);
    QVector<Blob> Calculate();
};

#endif // COMPUTEALGORITHM_H
