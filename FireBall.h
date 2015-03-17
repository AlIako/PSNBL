#ifndef FIREBALL_H_INCLUDED
#define FIREBALL_H_INCLUDED
#include "Object.h"

class Fireball: public Object
{
public:
    Fireball();
    virtual void ini();
    virtual void update(double functionTime);
    virtual void draw();

    virtual void action(int type, Object* o=NULL);
private:
    Texture* m_texture_fire;
};


#endif // FIREBALL_H_INCLUDED
