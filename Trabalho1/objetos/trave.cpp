
#include "trave.h"

Trave::Trave()
{
    nomeObjeto = "Trave";
}

void Trave::estaca()
{
    // Face frente
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glVertex3f(0, 0, 0.08);
        glVertex3f(0.08, 0, 0.08);
        glVertex3f(0.08, 1.0, 0.08);
        glVertex3f(0, 1.0, 0.08);
    glEnd();

    // Face trás
    glBegin(GL_QUADS);
        glNormal3f(0, 0, -1);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1.0, 0);
        glVertex3f(0.08, 1.0, 0);
        glVertex3f(0.08, 0, 0);
    glEnd();

    // Face direita
    glBegin(GL_QUADS);
        glNormal3f(1, 0, 0);

        glVertex3f(0.08, 0, 0.08);
        glVertex3f(0.08, 0, 0);
        glVertex3f(0.08, 1.0, 0);
        glVertex3f(0.08, 1.0, 0.08);
    glEnd();

    // Face esquerda
    glBegin(GL_QUADS);
        glNormal3f(-1, 0, 0);
        glVertex3f(0, 0, 0.08);
        glVertex3f(0, 1.0, 0.08);
        glVertex3f(0, 1.0, 0);
        glVertex3f(0, 0, 0);
    glEnd();

    // Face superior
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(0, 1.0, 0);
        glVertex3f(0, 1.0, 0.08);
        glVertex3f(0.08, 1.0, 0.08);
        glVertex3f(0.08, 1.0, 0);
    glEnd();

    // Face inferior
    glBegin(GL_QUADS);
        glNormal3f(0, -1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0.08, 0, 0);
        glVertex3f(0.08, 0, 0.08);
        glVertex3f(0, 0, 0.08);
    glEnd();
}

void Trave::estacaSuperior()
{
    // Face frente
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 0.08);
        glVertex3f(0, 0, 0.08);
        glVertex3f(0.08, 0, 0.08);
        glVertex3f(0.08, 2.5, 0.08);
        glVertex3f(0, 2.5, 0.08);
    glEnd();

    // Face trás
    glBegin(GL_QUADS);
        glNormal3f(0, 0, -1);

        glVertex3f(0, 0, 0);
        glVertex3f(0, 2.5, 0);
        glVertex3f(0.08, 2.5, 0);
        glVertex3f(0.08, 0, 0);
    glEnd();

    // Face direita
    glBegin(GL_QUADS);
        glNormal3f(1, 0, 0);
        glVertex3f(0.08, 0, 0.08);
        glVertex3f(0.08, 0, 0);
        glVertex3f(0.08, 2.5, 0);
        glVertex3f(0.08, 2.5, 0.08);
    glEnd();


    // Face esquerda
    glBegin(GL_QUADS);
        glNormal3f(-1, 0, 0);
        glVertex3f(0, 0, 0.08);
        glVertex3f(0, 2.5, 0.08);
        glVertex3f(0, 2.5, 0);
        glVertex3f(0, 0, 0);
    glEnd();

    // Face superior
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(0, 2.5, 0);
        glVertex3f(0, 2.5, 0.08);
        glVertex3f(0.08, 2.5, 0.08);
        glVertex3f(0.08, 2.5, 0);
    glEnd();

    // Face inferior
    glBegin(GL_QUADS);
        glNormal3f(0, -1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0.08, 0, 0);
        glVertex3f(0.08, 0, 0.08);
        glVertex3f(0, 0, 0.08);
    glEnd();
}

void Trave::desenha()
{
    glPushMatrix();
        Objeto::desenha();

        if (selecionado) {
            GUI::setColor(1, 1, 1);
        } else {
            GUI::setColor(3, 3, 3);
        }

        // Lado esquerdo
        glTranslatef(-2, 0, 0);
        glRotatef(0, 0, 0, 0);
        glScalef(1, 1, 1);
        estaca();

        // Lado direito
        glTranslatef(2.58, 0, 0);
        glRotatef(0, 0, 0, 0);
        glScalef(1, 1, 1);
        estaca();

        // Estaca superior
        glTranslatef(0, 1.0, 0);
        glRotatef(90, 1, 0, 0);
        glRotatef(90, 0, 0, 1);
        glScalef(1, 1, 1);
        estacaSuperior();
    glPopMatrix();
}

void Trave::salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo)
{
    t.x = tx;
    t.y = ty;
    t.z = tz;
    a.x = ax;
    a.y = ay;
    a.z = az;
    s.x = sx;
    s.y = sy;
    s.z = sz;
    selecionado = isSelecionado;
    eixos = eixo;
}
