#include <QtWidgets>
#include <QtOpenGL>

#include <math.h>

#include "fertilizer.h"
#include "qtmodel.h"

Seed::Seed()
{
    this->position = QVector3D(0.0f, 0.0f, 0.0f);
    this->buds = QVector<Bud>();
}

Seed::Seed(QVector3D position)
{
    this->position = position;
    this->buds = QVector<Bud>();
}

void drawCube(QVector3D offset, QColor color, float scale)
{
    static const float vertices[6][4][3] = {
            { { 1.0, -1.0, 1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { 1.0, 1.0, 1.0 } },
            { { -1.0, -1.0, -1.0 }, { -1.0, -1.0, 1.0 }, { -1.0, 1.0, 1.0 }, { -1.0, 1.0, -1.0 } },
            { { 1.0, -1.0, -1.0 }, { -1.0, -1.0, -1.0 }, { -1.0, 1.0, -1.0 }, { 1.0, 1.0, -1.0 } },
            { { -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } },
            { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, -1.0, 1.0 }, { -1.0, -1.0, 1.0 } },
            { { -1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 } }
        };

    static const float normals[6][3] = {
            { 1, 0, 0 }, { -1, 0, 0 }, { 0, 0, -1 }, { 0, 0, 1 }, { 0, -1, 0 }, { 0, 1, 0 }
        };

    glPushMatrix();
    glTranslatef(offset.x(), offset.y(), offset.z());
    glScalef(scale, scale, scale);
    glColor3f(color.redF(), color.greenF(), color.blueF());

    for (int i = 0; i < 6; ++i) {
        glBegin(GL_QUADS);

        glNormal3fv(normals[i]);
        for (int j = 0; j < 4; ++j)
        {
            glVertex3fv(vertices[i][j]);
        }

        glEnd();
    }
    glPopMatrix();
}

void drawSphere(QVector3D offset, QColor color, float scale, int lats, int longs) {
    glPushMatrix();
    glTranslatef(offset.x(), offset.y(), offset.z());
    glScalef(scale, scale, scale);
    glColor3f(color.redF(), color.greenF(), color.blueF());

    int i, j;
    for(i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
    glPopMatrix();
}

Fertilizer::Fertilizer()
{
    this->drawSeeds = true;
    this->drawNutrients = true;
    this->numberOfNutrients = 100;
    this->nutrientRadius = 0.1f;
    this->budStepSize = 0.2f;
    this->budStrengthMultiplier = 0.1f;
}

float Fertilizer::getStrength(QVector3D position)
{
    if (this->gardener == NULL || !this->gardener->isInside(position)) {
        return 0.0f;
    }

    return this->compute(position);
}

void Fertilizer::draw()
{
    auto sphere = new QtSphere();
    if (this->drawSeeds) {
        glColor3i(0, 0, 0);
        for (int i=0; i<this->seeds.size(); i++) {
            auto pos = this->seeds[i].position;

            //drawSphere(this->seeds[i], black, 1, 16, 16);
            glPushMatrix();
            glTranslatef(pos.x(), pos.y(), pos.z());

            sphere->draw();

            glPopMatrix();
        }
    }

    if (this->drawNutrients) {
        glColor3i(0, 255, 0);
        for (int i=0; i<this->nutrients.size(); i++) {
            auto pos = this->nutrients[i];

            //drawSphere(this->nutrients[i], black, 1, 16, 16);
            //drawCube(this->nutrients[i], green, 1);
            glPushMatrix();
            glTranslatef(-0.125f, -0.125f, -0.125f);
            glTranslatef(pos.x(), pos.y(), pos.z());

            sphere->draw();

            glPopMatrix();
        }
    }

    //drawCube(QVector3D(0,0,0), QColor::fromRgb(0, 255, 0), 0.1);

}

void Fertilizer::setup(Gardener *gardener)
{
    this->gardener = gardener;
}

