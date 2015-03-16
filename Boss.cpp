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




string Boss::writeObj()
{

    std::ostringstream oss;

    oss << Object::writeObj();

    oss<<" name: " << m_name;

    return oss.str();
}




void Boss::iniPattern(BossPattern* pat)
{

}

