#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED
#include "Object.h"


class BossPattern
{
public:
    BossPattern();


    string name;
    int duration;
    GTime time_since_start;

private:
};




class Boss: public Object
{
public:
    Boss();
    virtual void ini();
    virtual void update(double functionTime);

    virtual string writeObj();

    virtual void iniPattern(BossPattern* pat);

protected:
    string m_phase;
    vector<BossPattern> m_patterns;
    BossPattern* m_current_pattern;

    Vector3D m_destination;
};




#endif // BOSS_H_INCLUDED
