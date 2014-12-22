#include "Object.h"



Object::Object()
{
    m_position=Vector3D(0,0,0);
    m_rotation=Vector3D(0,0,0);
    m_size=Vector3D(1,1,1);
    m_type="object";
    m_speed=1;

    gtext=NULL;
}





void Object::ini()
{
    //cerr <<"ini "<<m_type<<endl;
}

void Object::draw()
{

}




bool Object::collision(Object* o)
{
    double marge=0.2;
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
    return false;
}
















