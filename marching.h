#ifndef MARCHING_H
#define MARCHING_H

#include <QVector3D>
#include <QGLWidget>
#include <math.h>

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
    bool bSpin;
    bool bMove;
    bool bLight;
    float time = 0.0f;

    void GetNormal(QVector3D &rfNormal, float fX, float fY, float fZ);
    float Sample1(float fX, float fY, float fZ);
    float Sample2(float fX, float fY, float fZ);
    float Sample3(float fX, float fY, float fZ);
    float (Marching::*Sample)(float fX, float fY, float fZ);
    void MarchCube1(float fX, float fY, float fZ, float fScale);
    void MarchCube2(float fX, float fY, float fZ, float fScale);
    void (Marching::*MarchCube)(float fX, float fY, float fZ, float fScale);
    void MarchTetrahedron(QVector3D *pasTetrahedronPosition, float *pafTetrahedronValue);

public:
    float Pitch = 0.0f;
    float Yaw   = 0.0f;

    Marching();
    void SetTime(float fTime);
    void MarchingCubes();
    void Draw();
};


#endif // MARCHING_H
