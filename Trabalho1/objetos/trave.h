#ifndef TRAVE_H
#define TRAVE_H

#include <objeto.h>

class Trave : public Objeto
{
public:
    Trave();
    void estaca();
    void estacaSuperior();
    void desenha();
    void salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo);

};

#endif // TRAVE_H
