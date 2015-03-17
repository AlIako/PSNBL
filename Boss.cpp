#include "Boss.h"


BossPattern::BossPattern()
{

}

Boss::Boss()
{
    m_type="boss";
    m_name="boss";
    m_current_pattern=NULL;

    m_speed=.5;
    m_gravity=false;
}




void Boss::ini()
{
    m_patterns.clear();
}


void Boss::update(double functionTime)
{
    ft=functionTime;
}


void Boss::action(int type, Object* o)
{
    if(type==0)//start boss
    {
        m_active=true;

        if(m_patterns.size()>0)
        {
            m_current_pattern=&m_patterns[0];
            iniPattern(m_current_pattern);
            time_since_ini.reset();
        }
    }
}


string Boss::writeObj()
{

    std::ostringstream oss;

    oss << Object::writeObj();

    oss<<" name: " << m_name;

    return oss.str();
}




void Boss::iniPattern(BossPattern* pat)
{
    if(pat!=NULL)
        pat->time_since_start.reset();
}

