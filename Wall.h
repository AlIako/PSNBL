#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED
#include "Block.h"

class Wall: public Block
{
    public:
    Wall();

    virtual void ini();
    virtual void draw();
    private:
};


#endif // WALL_H_INCLUDED
