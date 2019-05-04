#include "palmeira.h"

Palmeira::Palmeira()
{
    model = new Model3DS("../3ds/palmeira/palmtree.3ds");
    nomeObjeto = "Palmeira";
}

void Palmeira::desenha()
{
    glPushMatrix();
        Objeto::desenha();

        if (selecionado) {
            glColor3d(0, 1, 0);
        }

        glTranslatef(0, 2.55, 0);
        glRotatef(-90, 1, 0, 0);
        glScalef(0.00035, 0.00035, 0.00035);

        model->draw();
    glPopMatrix();
}

void Palmeira::salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo)
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
