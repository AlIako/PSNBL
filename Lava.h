#ifndef LAVA_H_INCLUDED
#define LAVA_H_INCLUDED
#include "Bubble.h"

class Lava: public Object
{
    public:
    Lava();

    virtual void ini();
    virtual void update(double functionTime);
    virtual void draw();

    private:
    vector<Bubble> m_bubbles;
    vector<Bubble> m_steam;
    Texture* m_texture;
    double mosaic;

    Vector3D txtcord;

    DRDampingSpring dampvalue;
};
#endif // LAVA_H_INCLUDED
