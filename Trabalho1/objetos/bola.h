#ifndef BOLA_H
#define BOLA_H

#include <objeto.h>

class Bola : public Objeto
{
public:
    Bola();
    void desenha();
    void salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo);

};

#endif // BOLA_H
