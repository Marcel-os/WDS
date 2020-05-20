#ifndef ROCKET_H
#define ROCKET_H

/*!
* \file
* \brief Definicja klasy Rocket
*
* Plik zawiera definicję klasy Rocket.
*/

#include <qopengl.h>
#include <QVector>
#include <QVector3D>

/*!
* \brief Tworzy obiekt modelu rakiety 3D
*
* Obiekt modelu rakiety, wykorzystywany w widgecie opengl
* do wizualizacji położenia.
*/

class Rocket
{
public:
    Rocket();
    const GLfloat *constData() const { return m_data.constData(); }
    int count() const { return m_count; }
    int vertexCount() const { return m_count / 6; }

private:
    /*!
    * \brief wyciągnięcie czworokąta na większą długość.
    */
    void quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4);
    /*!
    * \brief wyciągnięcie powierzchni na większą długość.
    */
    void extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
    /*!
    * \brief wyciągnięcie czworokąta na mnijszą długość.
    */
    void quad2(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4);
    /*!
    * \brief wyciągnięcie powierzchni na mnijszą długość.
    */
    void extrude2(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
    /*!
    * \brief wyciągnięcie trójkąta.
    */
    void triangle(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3);
    /*!
    * \brief Dodanie elementów do widgetu.
    */
    void add(const QVector3D &v, const QVector3D &n);

    QVector<GLfloat> m_data;
    int m_count;
};

#endif // Rocket_H
