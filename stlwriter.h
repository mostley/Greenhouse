#ifndef STLWRITER_H
#define STLWRITER_H

#include <QString>
#include <QVector>
#include <QFile>

#include "triangle.h"

class StlWriter
{
public:
    StlWriter();

    void writeStl(QString destination, QVector<Triangle*>* triangles, bool writeBinary);

private:
    void writeAscii(QFile* file, QVector<Triangle*>* triangles);
    void writeBinary(QFile* file, QVector<Triangle*>* triangles);

};

#endif // STLWRITER_H
