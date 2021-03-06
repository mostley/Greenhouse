#ifndef QTMODEL_H
#define QTMODEL_H

#include <QObject>
#include <QColor>

class Patch;
struct Geometry;

class QtModel
{
public:
    QtModel();
    QtModel(int d, qreal s);
    ~QtModel();
    void setColor(QColor c);
    void draw() const;
protected:
    virtual void buildGeometry(int d, qreal s);

    QList<Patch *> parts;
    Geometry *geom;
};

class QtSphere : public QtModel
{
public:
    explicit QtSphere(int d = 64, qreal s = 1.0);
private:
    void buildGeometry(int d, qreal s);
};

#endif // QTMODEL_H
