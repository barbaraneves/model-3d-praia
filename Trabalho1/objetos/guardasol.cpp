#include "guardasol.h"

GuardaSol::GuardaSol()
{
    model = new Model3DS("../3ds/guarda-sol/3d-model.3ds");
    nomeObjeto = "GuardaSol";
}

void GuardaSol::desenha()
{
    glColor3d(0.0, 100.0, 0.0);

    glPushMatrix();
        Objeto::desenha();

        glTranslatef(0, 0, 0);
        glRotatef(-90, 1, 0, 0);
        glScalef(0.008, 0.008, 0.008);

        model->draw();
    glPopMatrix();
}

void GuardaSol::salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo)
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
