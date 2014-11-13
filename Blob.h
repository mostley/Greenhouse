#ifndef BLOB_H
#define BLOB_H

#include <QVector3D>

enum BlobMode { BLOB_MODE_ADD, BLOB_MODE_SUBSTRACT, BLOB_MODE_INTERSECT };

class Blob
{
public:
    float radius;
    QVector3D position;
    BlobMode mode;
};

#endif // BLOB_H
