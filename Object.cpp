#include "Object.h"
#define CD_LOSE_LIFE 1000


Object::Object()
{
    m_position=Vector3D(0,0,0);
    m_rotation=Vector3D(0,0,0);
    m_velocity=Vector3D(0,0,0);
    m_size=Vector3D(1,1,1);
    m_type="object";
    m_speed=0.01;

    m_gravity=true;
    m_physical=false;

    gtext=NULL;

    m_transparency=false;
    m_block=true;
    m_destructible=false;
    m_life=100;

    m_collided=false;
    ft=0;

    m_idOnline=-1;
}

void Object::resurrect()
{
    m_life=4;
    m_position=Vector3D(0,0,40);
    m_rotation=Vector3D(0,0,0);
    m_velocity=Vector3D(0,0,0);
}

void Object::loseLife(double value)
{
    last_lose_life.couler();
    if(last_lose_life.ecouler(CD_LOSE_LIFE))
    {
        last_lose_life.reset();
        m_life-=value;
    }
}

void Object::update(double functionTime)
{
    ft=functionTime;

    //kill if out of map
    if(m_position.Z<=-50)
        m_life=0;

    //rez if killed
    if(m_life<=0)
        resurrect();

    if(m_collided)
        m_collided=false;
}


void Object::ini()
{
    //cerr <<"ini "<<m_type<<endl;
}

void Object::draw()
{

}

void Object::applyGravity()
{
    if(m_physical)
    {
        m_velocity.Z-=0.01*ft;
    }
}


void Object::applyPhysics()
{
    applyPhysics(1,1,1);
}


void Object::applyPhysics(int x, int y, int z)
{
    if(x)
        m_position.X+=m_velocity.X;
    if(y)
        m_position.Y+=m_velocity.Y;
    if(z)
        m_position.Z+=m_velocity.Z;
}


bool Object::collidedWithType(std::string t)
{
    for(unsigned int i=0,count=m_colliding.size();i<count;i++)
    {
        if(m_colliding[i]->getType()==t)
            return true;
    }
    return false;
}


bool Object::collision(Object* o)
{
    if((o->getType()=="rope" && m_type=="player") || (o->getType()=="player" && m_type=="rope"))
        return false;


    double marge=0.2*0;
    Vector3D m_taille_col=m_size;
    m_taille_col.X-=marge;
    m_taille_col.Y-=marge;
    m_taille_col.Z-=marge;

    Vector3D m_taille_colB=o->getSize();
    m_taille_colB.X-=marge;
    m_taille_colB.Y-=marge;
    m_taille_colB.Z-=marge;

    if(m_position.X-m_taille_col.X<o->getPos().X+m_taille_colB.X && m_position.X+m_taille_col.X>o->getPos().X-m_taille_colB.X &&
       m_position.Y-m_taille_col.Y<o->getPos().Y+m_taille_colB.Y && m_position.Y+m_taille_col.Y>o->getPos().Y-m_taille_colB.Y &&
       m_position.Z<o->getPos().Z+2*m_taille_colB.Z&& m_position.Z+2*m_taille_col.Z>o->getPos().Z)
        return true;
    /*if(m_position.X-m_taille_col.X<o->getPos().X+m_taille_colB.X && m_position.X+m_taille_col.X>o->getPos().X-m_taille_colB.X &&
       m_position.Y-m_taille_col.Y<o->getPos().Y+m_taille_colB.Y && m_position.Y+m_taille_col.Y>o->getPos().Y-m_taille_colB.Y &&
       m_position.Z<o->getPos().Z+2*m_taille_colB.Z&& m_position.Z+2*m_taille_col.Z>o->getPos().Z)
        return true;*/
    return false;
}
















