#ifndef CASA_H
#define CASA_H

#include <objeto.h>
#include <porta.h>

class Casa : public Objeto
{
public:
    Casa();
    void desenha();
    void salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo);

private:
    Porta * porta;
};

#endif // CASA_H
