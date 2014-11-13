#ifndef QTMODEL_H
#define QTMODEL_H

#include <QObject>
#include <QColor>

class Patch;
struct Geometry;

class QtModel : public QObject
{
public:
    explicit QtModel(QObject *parent, int d = 64, qreal s = 1.0);
    ~QtModel();
    void setColor(QColor c);
    void draw() const;
private:
    void buildGeometry(int d, qreal s);

    QList<Patch *> parts;
    Geometry *geom;
};

#endif // QTMODEL_H
