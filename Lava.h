#ifndef LAVA_H_INCLUDED
#define LAVA_H_INCLUDED
#include "Object.h"

class Lava: public Object
{
    public:
    Lava();

    virtual void ini();
    virtual void draw();

    private:
    Texture* m_texture;
    double mosaic;
};
#endif // LAVA_H_INCLUDED
