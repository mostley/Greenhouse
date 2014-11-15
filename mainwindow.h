#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "ComputeAlgorithm.h"
#include "stlwriter.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QMenu;
class QSlider;
QT_END_NAMESPACE

class GLWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void about();

    void on_button_export_clicked();

private:
    Ui::MainWindow *ui;
    ComputeAlgorithm *algorithm;
    StlWriter* stlWriter;

    QVector<Triangle*>* createSample1();
    void deleteTrianglesVector(QVector<Triangle*>* triangles);
};

#endif
