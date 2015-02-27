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

    bool goingUp;

    double speedDie;
    double speedSize;
    int timeToPop;

    private:

    GTime timeTilPop;

    double zUp;
};

#endif // BUBBLE_H_INCLUDED
