#ifndef PALMEIRA_H
#define PALMEIRA_H

#include <objeto.h>

class Palmeira : public Objeto
{
public:
    Model3DS* model;
public:
    Palmeira();
    void desenha();
    void salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo);

};

#endif // PALMEIRA_H
