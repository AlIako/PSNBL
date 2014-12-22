#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "Object.h"

class Block: public Object
{
    public:
    Block();

    virtual void ini();
    virtual void draw();

    private:
    Texture* m_texture;
};

#endif // BLOCK_H_INCLUDED
