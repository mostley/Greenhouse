#ifndef MARCHING_H
#define MARCHING_H

#include <QVector>
#include <QVector3D>
#include <QGLWidget>
#include <math.h>

#include "fertilizer.h"

static const float afAmbientWhite [] = {0.25, 0.25, 0.25, 1.00};
static const float afAmbientRed   [] = {0.25, 0.00, 0.00, 1.00};
static const float afAmbientGreen [] = {0.00, 0.25, 0.00, 1.00};
static const float afAmbientBlue  [] = {0.00, 0.00, 0.25, 1.00};
static const float afDiffuseWhite [] = {0.75, 0.75, 0.75, 1.00};
static const float afDiffuseRed   [] = {0.75, 0.00, 0.00, 1.00};
static const float afDiffuseGreen [] = {0.00, 0.75, 0.00, 1.00};
static const float afDiffuseBlue  [] = {0.00, 0.00, 0.75, 1.00};
static const float afSpecularWhite[] = {1.00, 1.00, 1.00, 1.00};
static const float afSpecularRed  [] = {1.00, 0.25, 0.25, 1.00};
static const float afSpecularGreen[] = {0.25, 1.00, 0.25, 1.00};
static const float afSpecularBlue [] = {0.25, 0.25, 1.00, 1.00};

class Marching
{
private:
    int     iDataSetSize;
    float   fStepSize;
    float   fTargetValue;
    float   fTime;
    QVector3D  sSourcePoint[3];
    bool bMove;
    bool bLight;
    float time = 0.0f;
    QVector<QVector3D>* verticeBuffer;
    QVector<QVector3D>* normalsBuffer;

    Fertilizer* fertilizer;

    void getNormal(QVector3D &rfNormal, float fX, float fY, float fZ);
    float sample1(float fX, float fY, float fZ);
    float sample2(float fX, float fY, float fZ);
    float sample3(float fX, float fY, float fZ);
    void marchCube1(float fX, float fY, float fZ, float fScale);
    void marchCube2(float fX, float fY, float fZ, float fScale);
    void (Marching::*marchCube)(float fX, float fY, float fZ, float fScale);
    void marchTetrahedron(QVector3D *pasTetrahedronPosition, float *pafTetrahedronValue);

public:
    Marching();
    ~Marching();
    void setTime(float fTime);
    void marchingCubes();
    void draw();
    void setup(Fertilizer* fertilizer);

    QVector<QVector3D>* getVertices();
    QVector<QVector3D>* getNormals();
};


#endif // MARCHING_H
