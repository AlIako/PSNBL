#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "Object.h"

class Block: public Object
{
    public:
    Block();

    virtual void ini();
    virtual void draw();

    protected:
    double mosaic;

    int m_r;
    int m_g;
    int m_b;
};

#endif // BLOCK_H_INCLUDED
