#include <QtWidgets>

#include "glwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

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
