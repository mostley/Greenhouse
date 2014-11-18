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

    connect(ui->nutrientSlider, SIGNAL(valueChanged(int)), ui->glFrame, SLOT(setNutrientAmount(int)));
    connect(ui->glFrame, SIGNAL(nutrientAmountChanged(int)), ui->nutrientSlider, SLOT(setValue(int)));

    connect(ui->randomSeedSlider, SIGNAL(valueChanged(int)), ui->glFrame, SLOT(setRandomSeed(int)));
    connect(ui->glFrame, SIGNAL(randomSeedChanged(int)), ui->randomSeedSlider, SLOT(setValue(int)));

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
    //QVector<Triangle*>* triangles = this->createSample1();
    auto triangles = new QVector<Triangle>;
    this->ui->glFrame->getTriangles(triangles);

    auto homePath = QStandardPaths::writableLocation(( QStandardPaths::HomeLocation));
    auto fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Export to STL File"),
                                                    homePath,
                                                    tr("STL (*.stl)"));

    if (fileName.isEmpty()) {
        return;
    }

    this->stlWriter->writeStl(fileName, triangles, false);

    delete triangles;
}

QVector<Triangle>* MainWindow::createSample1()
{
    QVector<Triangle>* triangles = new QVector<Triangle>;

    auto triangle = Triangle();
    triangle.normal = QVector3D(1.0f, 1.0f, 1.0f);
    triangle.v1 = QVector3D(1.0f, 0.0f, 0.0f);
    triangle.v2 = QVector3D(0.0f, 1.0f, 0.0f);
    triangle.v3 = QVector3D(0.0f, 0.0f, 1.0f);
    triangles->append(triangle);

    triangle = Triangle();
    triangle.normal = QVector3D(1.0f, 1.0f, 1.0f);
    triangle.v1 = QVector3D(2.0f, 0.0f, 0.0f);
    triangle.v2 = QVector3D(0.0f, 2.0f, 0.0f);
    triangle.v3 = QVector3D(0.0f, 0.0f, 2.0f);
    triangles->append(triangle);

    return triangles;
}
