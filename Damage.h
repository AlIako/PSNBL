#ifndef DAMAGE_H_INCLUDED
#define DAMAGE_H_INCLUDED
#include "Object.h"

class Damage: public Object
{
public:
    Damage();

    virtual void ini();
    virtual void update(double functionTime);
    virtual void draw();

    virtual void action(int type, Object* o=NULL);

    void setDamageValue(double d){m_damageValue=d;}
    void setDamageType(int t){m_damageType=t;}

private:
    double m_damageValue;
    int m_damageType;
};


#endif // DAMAGE_H_INCLUDED
