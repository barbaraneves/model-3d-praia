#include "casa.h"
#include "porta.h"

Casa::Casa()
{
    nomeObjeto = "Casa";
    porta = new Porta();
}

void Casa::desenha()
{
    glPushMatrix();
        Objeto::desenha();

        if (selecionado) {
            GUI::setColor(0, 0, 1);
        } else {
            GUI::setColor(0.3, 1, 4);
        }

        // Frente
        glBegin(GL_QUADS);
            glNormal3f(0, 0, 1);
            glVertex3f(0, 0, 1);
            glVertex3f(1, 0, 1);
            glVertex3f(1, 1, 1);
            glVertex3f(0, 1, 1);
        glEnd();

        // Face de trás
        glBegin(GL_QUADS);
            glNormal3f(0, 0, -1);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 1, 0);
            glVertex3f(1, 1, 0);
            glVertex3f(1, 0, 0);
        glEnd();

        // Face direita
        glBegin(GL_QUADS);
            glNormal3f(1, 0, 0);
            glVertex3f(1, 0, 1);
            glVertex3f(1, 0, 0);
            glVertex3f(1, 1, 0);
            glVertex3f(1, 1, 1);
        glEnd();

        // Face esquerda
        glBegin(GL_QUADS);
            glNormal3f(-1, 0, 0);
            glVertex3f(0, 0, 1);
            glVertex3f(0, 1, 1);
            glVertex3f(0, 1, 0);
            glVertex3f(0, 0, 0);
        glEnd();

        // Face superior
        glBegin(GL_QUADS);
            glNormal3f(0, 1, 0);
            glVertex3f(0, 1, 0);
            glVertex3f(0, 1, 1);
            glVertex3f(1, 1, 1);
            glVertex3f(1, 1, 0);
        glEnd();

        // Face inferior
        glBegin(GL_QUADS);
            glNormal3f(0, -1, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(1, 0, 0);
            glVertex3f(1, 0, 1);
            glVertex3f(0, 0, 1);
        glEnd();

        // Telhado

        glPushMatrix();
            glTranslatef(0, 1, 0);
            glRotatef(-90, 0, 1, 0);
            glRotatef(-45, 1, 0, 0);
            glScalef(1, 1.4, 1);

            glBegin(GL_POLYGON);
                glNormal3f(0, 0, 1);
                glVertex3f(0, 0, 0);
                glVertex3f(1, 0, 0);
                glVertex3f(0.5, 0.5, 0);
            glEnd();
        glPopMatrix();

        // Frente
        glBegin(GL_POLYGON);
            glNormal3f(0, 1, 1);
            glVertex3f(0, 1, 1);
            glVertex3f(1, 1, 1);
            glVertex3f(0.5, 1.5, 0.5);
        glEnd();

        // Trás
        glBegin(GL_POLYGON);
            glNormal3f(0, 1, -1);
            glVertex3f(1 ,1, 0);
            glVertex3f(0, 1, 0);
            glVertex3f(0.5, 1.5, 0.5);
        glEnd();

        // Direita
        glBegin(GL_POLYGON);
            glNormal3f(1, 1, 0);
            glVertex3f(1, 1, 1);
            glVertex3f(1, 1, 0);
            glVertex3f(0.5, 1.5, 0.5);
        glEnd();

        porta->desenha();
    glPopMatrix();
}

void Casa::salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo)
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
