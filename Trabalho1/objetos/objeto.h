#ifndef OBJETO_H
#define OBJETO_H

#include <gui.h>

class Objeto
{
public:
    Vetor3D t = Vetor3D(0, 0, 0);
    Vetor3D a = Vetor3D(0, 0, 0);
    Vetor3D s = Vetor3D(1, 1, 1);

    // Diz se o objeto foi ou não selecionado
    bool selecionado = false;

    // Desenha ou não os eixos do objeto
    bool eixos = false;

    string nomeObjeto;

public:
    Objeto();
    virtual void desenha();
    virtual void salvarObjeto(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ax, GLfloat ay, GLfloat az, GLfloat sx, GLfloat sy, GLfloat sz, bool isSelecionado, bool eixo);
};

#endif // OBJETO_H
