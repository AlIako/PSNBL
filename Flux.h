#ifndef FLUX_H_INCLUDED
#define FLUX_H_INCLUDED
#include "Object.h"


class Flux: public Object
{
public:
    Flux();

    virtual void ini();
    virtual void draw();

    virtual void update(double functionTime);

private:
    bool goingUp;
    double zOffset;
};


#endif // FLUX_H_INCLUDED
