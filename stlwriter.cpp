#include "stlwriter.h"

#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

StlWriter::StlWriter()
{
}

void StlWriter::writeStl(QString destination, QVector<Triangle*>* triangles, bool writeBinary)
{
    if (triangles == NULL) {
        qDebug() << "Error, triangles null";
        return;
    }

    if (triangles->count() == 0) {

        QMessageBox msgBox;
        msgBox.setText("No triangles to export.");
        msgBox.exec();
        return;
    }

    QFile file(destination);

//    if (file.exists()) {
//        QMessageBox msgBox;
//        msgBox.setText("The file already exist. Overwrite?");
//        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
//        int ret  = msgBox.exec();

//        if (ret != QMessageBox::Ok) {
//            return;
//        }
//    }

    file.open(QIODevice::WriteOnly);

    if (writeBinary) {
        this->writeBinary(&file, triangles);
    } else {
        this->writeAscii(&file, triangles);
    }

    file.close();
}

void StlWriter::writeAscii(QFile *file, QVector<Triangle*>* triangles)
{

    QTextStream  out(file);

    // write header
    out << QString("solid GreenhouseShape\n");

    // write triangles
    for (int i = 0; i < triangles->size(); i++) {
        auto trinangle = triangles->at(i);
        out << QString(" facet normal %0 %1 %2\n").arg(trinangle->normal.x()).arg(trinangle->normal.y()).arg(trinangle->normal.z());
        out << QString("  outer loop\n");

        out << QString("   vertex  %0 %1 %2\n").arg(trinangle->v1.x()).arg(trinangle->v1.y()).arg(trinangle->v1.z());
        out << QString("   vertex  %0 %1 %2\n").arg(trinangle->v2.x()).arg(trinangle->v2.y()).arg(trinangle->v2.z());
        out << QString("   vertex  %0 %1 %2\n").arg(trinangle->v3.x()).arg(trinangle->v3.y()).arg(trinangle->v3.z());

        out << QString("  endloop\n");
        out << QString(" endfacet\n");
    }

    // write footer
    out << QString("endsolid GreenhouseShape");
}

void StlWriter::writeBinary(QFile *file, QVector<Triangle*>* triangles)
{
  Q_UNUSED(file);
  Q_UNUSED(triangles);
}
