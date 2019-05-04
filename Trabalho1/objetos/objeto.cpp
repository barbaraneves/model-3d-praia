#include "objeto.h"

Objeto::Objeto()
{

}

void Objeto::desenha()
{
    glTranslatef(t.x, t.y, t.z);
    glRotatef(a.z, 0, 0, 1);
    glRotatef(a.y, 0, 1, 0);
    glRotatef(a.x, 1, 0, 0);

    if (eixos) {
        GUI::drawOrigin(1);
    }

    glScalef(s.x, s.y, s.z);
}

void Objeto::salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo)
{

}

