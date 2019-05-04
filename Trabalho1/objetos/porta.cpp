#include "porta.h"

Porta::Porta()
{
    model = new Model3DS("../3ds/porta/3d-model.3ds");
    nomeObjeto = "Porta";
}

void Porta::desenha()
{
    glPushMatrix();
        glTranslatef(0.5, 0, 1.025);
        //glTranslatef(0.5, 0, 0);
        glRotatef(-90, 1, 0, 0);
        glRotatef(180, 0, 0, 1);
        glScalef(0.0075, 0.0075, 0.0075);

        model->draw();
    glPopMatrix();
}
