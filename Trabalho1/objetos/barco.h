#ifndef BARCO_H
#define BARCO_H

#include <objeto.h>

class Barco : public Objeto
{
public:
    Model3DS* model;
public:
    Barco();
    void desenha();
    void salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo);

};

#endif // BARCO_H
