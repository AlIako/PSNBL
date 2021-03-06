#ifndef ENDLEVEL_H_INCLUDED
#define ENDLEVEL_H_INCLUDED
#include "Object.h"

class EndLevel: public Object
{
    public:
    EndLevel();

    virtual void ini();
    virtual void draw();

    virtual void action(int type, Object* o=NULL);

    protected:
    Vector3D dirmov;
    Vector3D txtcord;
};




#endif // ENDLEVEL_H_INCLUDED
