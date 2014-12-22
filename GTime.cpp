#include "GTime.h"


GTime::GTime()
{
    m_stop=false;
    temps_coule=false;
    m_tempsActuel=0;
    m_tempsPrecedent=0;
}

void GTime::rapport(string t)
{
    cerr << t << ": " << timePast() << endl;
}
void GTime::reset()
{
    m_tempsPrecedent=SDL_GetTicks();
    m_tempsActuel=m_tempsPrecedent;
    temps_coule=true;
    m_stop=false;
}

void GTime::setTimePast(int t)
{
    reset();
    m_tempsPrecedent-=t;
}

void GTime::couler()
{
    if(m_stop)
        m_tempsPrecedent+=SDL_GetTicks()-m_tempsActuel;
    m_tempsActuel=SDL_GetTicks();
}
void GTime::stopper()
{
    m_stop=true;
}
void GTime::relancer()
{
    m_stop=true;
}

bool GTime::ecouler(int v)
{
    if(m_tempsActuel-m_tempsPrecedent>=v)
        return true;
    return false;
}

std::string GTime::getType()
{
    return m_type;
}
int GTime::timePast()
{
    return m_tempsActuel-m_tempsPrecedent;
}
