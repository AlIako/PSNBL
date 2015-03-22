#ifndef BOSSBUTAN_H_INCLUDED
#define BOSSBUTAN_H_INCLUDED
#include "Boss.h"

class BossButan: public Boss
{
public:
    BossButan();

    virtual void ini();
    virtual void update(double functionTime);

    virtual void draw();

    virtual void iniPattern(BossPattern* pat);

    virtual void action(int type, Vector3D v);
    virtual void action(int type, Object* o=NULL);

private:
    Texture* m_texture_fire;
    GTime cd_fireball;

};


#endif // BOSSBUTAN_H_INCLUDED
