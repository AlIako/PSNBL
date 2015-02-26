#include "Spell.h"
/*
lanceur de disque: destroy friends' ropes
long jump shift+space
run (require energy)
*/


Spell::Spell()
{
    m_required="nothing";
    m_name="spell";
    m_cooldown=1000;
    m_lastCast.reset();
}



void Spell::update(double functionTime)
{

}


bool Spell::cast()
{
    m_lastCast.couler();
    if(m_lastCast.ecouler(m_cooldown))
    {
        m_lastCast.reset();
        return true;
    }
    return false;
}
