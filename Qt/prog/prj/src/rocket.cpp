#include "rocket.h"
#include <qmath.h>

/*!
* \file
* \brief Definicja metod klasy Rocket
*
* Zawiera definicje metod klasy Rocket.
*/

Rocket::Rocket()
    : m_count(0)
{
    m_data.resize(2500 * 6);
    const int NumSectors = 100;

    for (int i = 0; i < NumSectors; ++i) {
        GLfloat angle = (i * 2 * M_PI) / NumSectors;
        GLfloat angleSin = qSin(angle);
        GLfloat angleCos = qCos(angle);
        const GLfloat x5 = 0.03f * angleSin;
        const GLfloat y5 = 0.03f * angleCos;
        const GLfloat x6 = 0.00f * angleSin;
        const GLfloat y6 = 0.00f * angleCos;

        angle = ((i + 1) * 2 * M_PI) / NumSectors;
        angleSin = qSin(angle);
        angleCos = qCos(angle);
        const GLfloat x7 = 0.00f * angleSin;
        const GLfloat y7 = 0.00f * angleCos;
        const GLfloat x8 = 0.03f * angleSin;
        const GLfloat y8 = 0.03f * angleCos;

        quad(x5, y5, x6, y6, x7, y7, x8, y8);
        //extrude(x6, y6, x7, y7);
        extrude(x8, y8, x5, y5);
        triangle(x8, y8,0.28f,x5, y5,0.28f,0.0f,0.0f,0.5f);
    }

      quad2(0.06f, 0.004f, 0.06f, -0.004f, 0.03f, -0.004f, 0.03f, 0.004f);
      quad2(-0.03f, 0.004f, -0.06f, 0.004f, -0.06f, -0.004f, -0.03f, -0.004f);
      quad2(0.004f, 0.03f, 0.004f, 0.06f, -0.004f, 0.06f, -0.004f, 0.03f);
      quad2(0.004f, -0.03f, 0.004f, -0.06f, -0.004f, -0.06f, -0.004f, -0.03f);

      extrude2(0.06f, 0.004f, 0.06f, -0.004f);
      extrude2(0.06f, -0.004f, 0.03f, -0.004f);
      extrude2(0.03f, -0.004f, 0.03f, 0.004f);
      extrude2(0.03f, 0.004f, 0.06f, 0.004f);

      extrude2(-0.03f, 0.004f, -0.06f, 0.004f);
      extrude2(-0.06f, 0.004f, -0.06f, -0.004f);
      extrude2( -0.06f, -0.004f, -0.03f, -0.004f);
      extrude2( -0.03f, -0.004f, -0.03f, 0.004f);

      extrude2(0.004f, 0.03f, 0.004f, 0.06f);
      extrude2(0.004f, 0.06f, -0.004f, 0.06f);
      extrude2(-0.004f, 0.06f, -0.004f, 0.03f);
      extrude2(-0.004f, 0.03f, 0.004f, 0.03f);

      extrude2(0.004f, -0.03f, 0.004f, -0.06f);
      extrude2(0.004f, -0.06f, -0.004f, -0.06f);
      extrude2(-0.004f, -0.06f, -0.004f, -0.03f);
      extrude2(-0.004f, -0.03f, 0.004f, -0.03f);

}

void Rocket::add(const QVector3D &v, const QVector3D &n)
{
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    m_count += 6;
}

void Rocket::quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
{
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, -0.28f), n);
    add(QVector3D(x4, y4, -0.28f), n);
    add(QVector3D(x2, y2, -0.28f), n);

    add(QVector3D(x3, y3, -0.28f), n);
    add(QVector3D(x2, y2, -0.28f), n);
    add(QVector3D(x4, y4, -0.28f), n);

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f), QVector3D(x2 - x4, y2 - y4, 0.0f));

    add(QVector3D(x4, y4, 0.28f), n);
    add(QVector3D(x1, y1, 0.28f), n);
    add(QVector3D(x2, y2, 0.28f), n);

    add(QVector3D(x2, y2, 0.28f), n);
    add(QVector3D(x3, y3, 0.28f), n);
    add(QVector3D(x4, y4, 0.28f), n);
}

void Rocket::extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, -0.1f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, +0.28f), n);
    add(QVector3D(x1, y1, -0.28f), n);
    add(QVector3D(x2, y2, +0.28f), n);

    add(QVector3D(x2, y2, -0.28f), n);
    add(QVector3D(x2, y2, +0.28f), n);
    add(QVector3D(x1, y1, -0.28f), n);
}

void Rocket::quad2(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4)
{
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, -0.28f), n);
    add(QVector3D(x4, y4, -0.28f), n);
    add(QVector3D(x2, y2, -0.28f), n);

    add(QVector3D(x3, y3, -0.28f), n);
    add(QVector3D(x2, y2, -0.28f), n);
    add(QVector3D(x4, y4, -0.28f), n);

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f), QVector3D(x2 - x4, y2 - y4, 0.0f));

    add(QVector3D(x4, y4, -0.15f), n);
    add(QVector3D(x1, y1, -0.15f), n);
    add(QVector3D(x2, y2, -0.15f), n);

    add(QVector3D(x2, y2, -0.15f), n);
    add(QVector3D(x3, y3, -0.15f), n);
    add(QVector3D(x4, y4, -0.15f), n);
}

void Rocket::extrude2(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, -0.1f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    add(QVector3D(x1, y1, -0.15f), n);
    add(QVector3D(x1, y1, -0.28f), n);
    add(QVector3D(x2, y2, -0.15f), n);

    add(QVector3D(x2, y2, -0.28f), n);
    add(QVector3D(x2, y2, -0.15f), n);
    add(QVector3D(x1, y1, -0.28f), n);
}

void Rocket::triangle(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    QVector3D n = QVector3D::normal(QVector3D(x1, y1, z1), QVector3D(x2, y2, z2), QVector3D(x3, y3, z3));

    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x2, y2, z2), n);
    add(QVector3D(x3, y3, z3), n);
}
