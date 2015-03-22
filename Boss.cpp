#include "Boss.h"
#include "Map.h"

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
    m_physical=true;

    target=NULL;
    nearPlayer=NULL;
    randPlayer=NULL;
}




void Boss::ini()
{
    m_patterns.clear();
}


void Boss::update(double functionTime)
{
    ft=functionTime;
    nearPlayer=nearestPlayer();

    time_til_resend.couler();
    if(time_til_resend.ecouler(100))
    {
        time_til_resend.reset();
        if(Online::getInstance()->inControl())
        {
            //send socket
            infosSocket s;
            s.confirmationID=-1;
            s.type=100;
            s.variable[0]=0;
            s.variable[1]=m_position.X;
            s.variable[2]=m_position.Y;
            s.variable[3]=m_position.Z;
            s.variable[4]=m_rotation.Z;
            s.variable[5]=m_life;
            Online::getInstance()->sendSocket(s);
        }
    }
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

void Boss::setPattern(string name)
{
    for(unsigned int i=0;i<m_patterns.size();i++)
        if(m_patterns[i].name==name)
            m_current_pattern=&m_patterns[i];
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


Object* Boss::nearestPlayer()
{
    Object* toReturn=NULL;
    double dis=999;
    double curDis=dis;
    vector<Player*>* p=Map::getInstance()->playerList;
    for(unsigned int i=0;i<p->size();i++)
    {
        curDis=((*p)[i]->getPos()-m_position).length();
        if((*p)[i]->getLife()>0 && curDis<dis)
        {
            dis=curDis;
            toReturn=(*p)[i];
        }
    }
    return toReturn;
}

Object* Boss::nearestPlayerFrom(Vector3D v)
{
    Object* toReturn=NULL;
    double dis=999;
    double curDis=dis;
    vector<Player*>* p=Map::getInstance()->playerList;
    for(unsigned int i=0;i<p->size();i++)
    {
        curDis=((*p)[i]->getPos()-v).length();
        if((*p)[i]->getLife()>0 && curDis<dis)
        {
            dis=curDis;
            toReturn=(*p)[i];
        }
    }
    return toReturn;
}

Object* Boss::randomPlayer()
{
    vector<Player*>* p=Map::getInstance()->playerList;

    int randInt=myIntRand(0,p->size()-1);

    return (*p)[randInt];
}





