#ifndef PORTA_H
#define PORTA_H

#include "objeto.h"

class Porta : public Objeto
{
public:
    Model3DS* model;
public:
    Porta();
    void desenha();
};

#endif // PORTA_H
