#include <QtWidgets>

#include "glwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "triangle.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->xSlider, SIGNAL(valueChanged(int)), ui->glFrame, SLOT(setXRotation(int)));
    connect(ui->glFrame, SIGNAL(xRotationChanged(int)), ui->xSlider, SLOT(setValue(int)));
    connect(ui->ySlider, SIGNAL(valueChanged(int)), ui->glFrame, SLOT(setYRotation(int)));
    connect(ui->glFrame, SIGNAL(yRotationChanged(int)), ui->ySlider, SLOT(setValue(int)));
    connect(ui->zSlider, SIGNAL(valueChanged(int)), ui->glFrame, SLOT(setZRotation(int)));
    connect(ui->glFrame, SIGNAL(zRotationChanged(int)), ui->zSlider, SLOT(setValue(int)));

    connect(this->ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(this->ui->actionAbout);
    menu.exec(event->globalPos());
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Menu"),
            tr("<b>Greenhouse</b> - Sculpting tool able to generate organic 3D models"));
}

void MainWindow::on_button_export_clicked()
{
    QVector<Triangle*>* triangles = this->createSample1();

    QString homePath = QStandardPaths::writableLocation(( QStandardPaths::HomeLocation));
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Export to STL File"),
                                                    homePath,
                                                    tr("STL (*.stl)"));

    if (fileName.isEmpty()) {
        return;
    }

    this->stlWriter->writeStl("E:\\dump\\test.stl", triangles, false);

    deleteTrianglesVector(triangles);
}

QVector<Triangle*> *MainWindow::createSample1()
{
    QVector<Triangle*>* triangles = new QVector<Triangle*>;

    Triangle* triangle = new Triangle();
    triangle->normal = QVector3D(1.0f, 1.0f, 1.0f);
    triangle->v1 = QVector3D(1.0f, 0.0f, 0.0f);
    triangle->v2 = QVector3D(0.0f, 1.0f, 0.0f);
    triangle->v3 = QVector3D(0.0f, 0.0f, 1.0f);
    triangles->append(triangle);

    triangle = new Triangle();
    triangle->normal = QVector3D(1.0f, 1.0f, 1.0f);
    triangle->v1 = QVector3D(2.0f, 0.0f, 0.0f);
    triangle->v2 = QVector3D(0.0f, 2.0f, 0.0f);
    triangle->v3 = QVector3D(0.0f, 0.0f, 2.0f);
    triangles->append(triangle);

    return triangles;
}

void MainWindow::deleteTrianglesVector(QVector<Triangle *> * triangles)
{
    for (int i = 0; i < triangles->size(); i++) {
        delete triangles->at(i);
    }
    delete triangles;
}
