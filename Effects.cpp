#include "Effects.h"


Effects* Effects::m_instance = new Effects();


Effects* Effects::getInstance()
{
    return m_instance;
}

Effects::Effects()
{
    m_explosions.clear();
}

void Effects::update(double functionTime)
{
    for(unsigned int i=0;i<m_explosions.size();i++)
    {
        m_explosions[i].update(functionTime);
        if(m_explosions[i].over())
            m_explosions.erase(m_explosions.begin()+i);
    }
}

void Effects::draw()
{
    for(unsigned int i=0;i<m_explosions.size();i++)
    {
        m_explosions[i].draw();
    }
}


void Effects::addExplosion(Vector3D position,string type)
{
    unsigned int ind=m_explosions.size();
    m_explosions.push_back(Explosion());

    m_explosions[ind].ini(type);
    m_explosions[ind].setPos(position);
}

