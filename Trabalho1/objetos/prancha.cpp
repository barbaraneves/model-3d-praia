#include "prancha.h"

Prancha::Prancha()
{
    model = new Model3DS("../3ds/prancha/Fish Textured.3ds");
    nomeObjeto = "Prancha";
}

void Prancha::desenha()
{
    glPushMatrix();
        if (selecionado) {
            glColor4d(1, 1, 1, 1);
        } else {
            glColor4d(1.0, 0.0, 0.0, 0.0);
        }

        Objeto::desenha();

        glTranslatef(-2.7, -0.615, 0);
        glRotatef(0, 1, 0, 0);
        glScalef(0.0008, 0.0008, 0.0008);

        model->draw();
    glPopMatrix();
}

void Prancha::salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo)
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
