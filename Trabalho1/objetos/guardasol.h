#ifndef GUARDASOL_H
#define GUARDASOL_H

#include <objeto.h>

class GuardaSol : public Objeto
{
public:
    Model3DS* model;
public:
    GuardaSol();
    void desenha();
    void salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo);
};

#endif // GUARDASOL_H
