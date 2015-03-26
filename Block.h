#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include "Object.h"

class Block: public Object
{
    public:
    Block();

    void action(int type, Object* o=NULL);

    virtual void ini();
    virtual void draw();
    void drawRight();
    void drawFront();
    void drawLeft();
    void drawBack();
    void drawTop();
    void drawBot();

    virtual string writeObj();

    protected:
    double mosaic;
    bool divided;

    int m_r;
    int m_g;
    int m_b;
};

#endif // BLOCK_H_INCLUDED
