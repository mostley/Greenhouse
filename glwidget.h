#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QVector>
#include <QTimer>
#include <QWheelEvent>
#include <QDebug>

#include "gardener.h"
#include "fertilizer.h"
#include "gardener.h"
#include "marching.h"
#include "triangle.h"
#include "potatofertilizer.h"

class QtModel;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void getTriangles(QVector<Triangle>* triangles);

public slots:
    void setNutrientAmount(int nutrientAmount);
    void setRandomSeed(int randomSeed);
    void setBudStrengthMultiplier(int budStrengthMultiplierPromille);

signals:
    void nutrientAmountChanged(int angle);
    void randomSeedChanged(int angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    QPoint lastPos;
    QColor qtGreen;
    QColor qtPurple;

    float xRot;
    float yRot;
    float zRot;
    float zoom;

    Marching* marching;
    Gardener* gardener;
    Fertilizer* fertilizer;

    void perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
    void updateGL();
};

#endif
