#include "barco.h"

Barco::Barco()
{
    model = new Model3DS("../3ds/barco/ship.3ds");
    nomeObjeto = "Barco";
}

void Barco::desenha()
{
    glPushMatrix();
        Objeto::desenha();

        if (selecionado) {
            glColor3d(0, 1, 0);
        }

        glTranslatef(0, 0.06, 0);
        glRotatef(-90, 1, 0, 0);
        glScalef(0.03, 0.03, 0.03);

        model->draw();
    glPopMatrix();
}

void Barco::salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo)
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
