#include <QtWidgets>
#include <QtOpenGL>

#include <math.h>

#include "glwidget.h"
#include "qtmodel.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    model = 0;
    xRot = 0.0f;
    yRot = 0.0f;
    zRot = 0.0f;

    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    this->marching = new Marching();
    this->fertilizer = new PotatoFertilizer();
    this->gardener = new Gardener(0.5, 0.5, 0.5);
    this->fertilizer->setup(this->gardener);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(1000.0f/30.0f);
}

GLWidget::~GLWidget()
{
    delete this->marching;
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
    {
        angle += 360 * 16;
    }
    while (angle > 360 * 16)
    {
        angle -= 360 * 16;
    }
}

void GLWidget::setNutrientAmount(int nutrientAmount)
{
    if (this->fertilizer->numberOfNutrients != nutrientAmount) {
        this->fertilizer->numberOfNutrients = nutrientAmount;
        emit nutrientAmountChanged(nutrientAmount);
        this->fertilizer->grow();
    }
}

void GLWidget::setRandomSeed(int randomSeed)
{
    if (this->gardener->randomSeed != randomSeed) {
        this->gardener->randomSeed = randomSeed;
        emit randomSeedChanged(randomSeed);
        this->gardener->init();
    }
}

void GLWidget::initializeGL()
{
    GLfloat afPropertiesAmbient [] = {0.50, 0.50, 0.50, 1.00};
    GLfloat afPropertiesDiffuse [] = {0.75, 0.75, 0.75, 1.00};
    GLfloat afPropertiesSpecular[] = {1.00, 1.00, 1.00, 1.00};

    qglClearColor(qtPurple.dark());
    glClearDepth( 1.0 );

    model = new QtModel(64, 1.0f);
    model->setColor(qtGreen.dark());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_MULTISAMPLE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // or: GL_LINE

    static GLfloat lightPosition[4] = { 0, 0, 1.0, 0.0 };//{ 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glLightfv( GL_LIGHT0, GL_AMBIENT,  afPropertiesAmbient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE,  afPropertiesDiffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, afPropertiesSpecular);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);

    glEnable( GL_LIGHT0 );

    glMaterialfv(GL_BACK,  GL_AMBIENT,   afAmbientGreen);
    glMaterialfv(GL_BACK,  GL_DIFFUSE,   afDiffuseGreen);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   afAmbientBlue);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   afDiffuseBlue);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  afSpecularWhite);
    glMaterialf( GL_FRONT, GL_SHININESS, 25.0);
}

void GLWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -1.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    //this->model->draw();

    if (this->fertilizer != NULL) {
        this->fertilizer->draw();
    }

    this->marching->setup(this->fertilizer);
    this->marching->draw();
}

void GLWidget::resizeGL(int width, int height)
{
    /*int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#else
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);*/


    float aspect, halfWorldSize = (1.4142135623730950488016887242097f/2);

    glViewport( 0, 0, width, height );
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    if (true) { // perspective or orthographic
        if(width <= height)
        {
            aspect = (float)height / (float)width;
            glOrtho(-halfWorldSize, halfWorldSize, -halfWorldSize*aspect,
                    halfWorldSize*aspect, -10*halfWorldSize, 10*halfWorldSize);
        }
        else
        {
            aspect = (float)width / (float)height;
            glOrtho(-halfWorldSize*aspect, halfWorldSize*aspect, -halfWorldSize,
                    halfWorldSize, -10*halfWorldSize, 10*halfWorldSize);
        }
    } else {
        this->perspective(60, 4.0f/3.0f, 0.1f, 100.0f);
    }

    glMatrixMode( GL_MODELVIEW );
}

void GLWidget::perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble xmin, xmax, ymin, ymax;

    ymax = zNear * tan( fovy * M_PI / 360.0 );
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustum( xmin, xmax, ymin, ymax, zNear, zFar );
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        xRot += 8 * dy;
        yRot += 8 * dx;
    } else if (event->buttons() & Qt::RightButton) {
        xRot += 8 * dy;
        zRot += 8 * dx;
    }
    lastPos = event->pos();
}

void GLWidget::mouseWheelEvent(QWheelEvent *event)
{
    auto dx = event->angleDelta();
    //TODO zoom
}

void GLWidget::getTriangles(QVector<Triangle>* triangles)
{
    QVector<QVector3D>* vertices = this->marching->getVertices();
    auto normals = this->marching->getNormals();

    for (auto j=0; j<vertices->count(); j+=3) {
        auto i = j/3;

        if (i >= triangles->count()) {
            triangles->append(Triangle());
        }

        Triangle& triangle = (*triangles)[i];
        triangle.v1 = vertices->at(j+0);
        triangle.v2 = vertices->at(j+1);
        triangle.v3 = vertices->at(j+2);
        triangle.normal = (normals->at(j+0) + normals->at(j+1) + normals->at(j+2)).normalized();
    }
}
