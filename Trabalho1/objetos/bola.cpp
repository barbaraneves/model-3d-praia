#include "bola.h"

Bola::Bola()
{
    nomeObjeto = "Bola";
}

void Bola::desenha()
{
    glPushMatrix();
        Objeto::desenha();

        if (selecionado) {
            GUI::setColor(1, 1, 1);
        } else {
            GUI::setColor(3, 3, 3);
        }

        GUI::drawSphere(0, 0.05, 0, 0.05);

        glTranslatef(0, 0, 0);
        glRotatef(0, 0, 0, 0);
        glScalef(0.00001, 0.00001, 0.00001);
    glPopMatrix();
}

void Bola::salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo)
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
