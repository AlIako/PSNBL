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

private:
    GTime cd_fireball;

};


#endif // BOSSBUTAN_H_INCLUDED
