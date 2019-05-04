#ifndef PRANCHA_H
#define PRANCHA_H

#include <objeto.h>

class Prancha : public Objeto
{
public:
    Model3DS* model;
public:
    Prancha();
    void desenha();
    void salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo);
};

#endif // PALMEIRA_H
