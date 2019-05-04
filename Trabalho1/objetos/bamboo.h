#ifndef BAMBOO_H
#define BAMBOO_H

#include <objeto.h>

class Bamboo : public Objeto
{
public:
    Model3DS* model;
public:
    Bamboo();
    void desenha();
    void salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo);
};

#endif // BAMBOO_H
