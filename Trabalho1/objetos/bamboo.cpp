#include "bamboo.h"

Bamboo::Bamboo()
{
    model = new Model3DS("../3ds/bamboo/Bamboo.3ds");
    nomeObjeto = "Bamboo";
}

void Bamboo::desenha()
{
    glPushMatrix();
        Objeto::desenha();

        glColor3d(0.0, 1.0, 0.0);
        glTranslatef(0, 0, 0);
        glRotatef(-90, 1, 0, 0);
        glScalef(0.0003, 0.0003, 0.0003);

        model->draw();
    glPopMatrix();
}

void Bamboo::salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo)
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
