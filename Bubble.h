#ifndef BUBBLE_H_INCLUDED
#define BUBBLE_H_INCLUDED
#include "Object.h"
#include "Vector3D.h"

class Bubble: public Object
{
    public:
    Bubble();
    virtual void ini();
    virtual void update(double functionTime);
    virtual void draw();

    void setTexture(Texture* t) {m_texture=t;}

    bool goingUp;

    double speedDie;
    double speedSize;
    int timeToPop;

    private:
    Texture* m_texture;

    GTime timeTilPop;

    double zUp;
};

#endif // BUBBLE_H_INCLUDED
