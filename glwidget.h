#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QVector>
#include <QTimer>

#include "gardener.h"
#include "fertilizer.h"
#include "marching.h"
#include "triangle.h"

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
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QtModel *model;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    QColor qtGreen;
    QColor qtPurple;

    Marching* marching;
    Gardener* gardener;
    Fertilizer* fertilizer;

    void perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
};

#endif
