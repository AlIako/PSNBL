#ifndef SPELL_H_INCLUDED
#define SPELL_H_INCLUDED
#include <string>
#include "GTime.h"

using namespace std;

class Spell
{
public:
    Spell();
    virtual void update(double functionTime);

    virtual bool cast();

    std::string getName() {return m_name;}
protected:
    string m_required;//require energy, mana, nothing?
    string m_name;
    int m_cooldown;
    GTime m_lastCast;
};


#endif // SPELL_H_INCLUDED
