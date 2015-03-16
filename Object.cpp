#include "Object.h"
#define CD_LOSE_LIFE 100


Object::Object()
{
    m_position=Vector3D(0,0,0);
    m_rotation=Vector3D(0,0,0);
    m_velocity=Vector3D(0,0,0);
    m_size=Vector3D(.5,.5,.5);
    m_type="object";
    m_name="name";
    m_speed=0.01;

    m_gravity=true;
    m_physical=false;

    m_transparency=false;
    m_block=true;
    m_destructible=false;
    m_life=100;
    m_lifeMax=100;

    m_hookable=false;

    m_collided=false;
    ft=0;

    m_idOnline=-1;
    m_onlineName="unnamed";

    m_onTopOf=NULL;

    m_texture=NULL;

    m_visible=true;
}

void Object::resurrect()
{
    m_life=4;
    m_position=Vector3D(0,0,40);
    m_rotation=Vector3D(0,0,0);
    m_velocity=Vector3D(0,0,0);
    m_colliding.clear();
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


    bool wasOnTop=false;
    if(m_onTopOf!=NULL)
    {
        wasOnTop=true;
        //m_onTopOf->setVisible(true);
        m_onTopOf=NULL;
    }
    if(m_collided)
    {
        m_collided=false;
        for(unsigned int i=0, count=m_colliding.size();i<count;i++)
        {
            if(m_colliding[i]->getType()=="lava")
            {
                if(getDestructible())
                {
                    loseLife(3);
                }

                //if we're too deep in the lava, instantly die
                if(m_position.Z<=m_colliding[i]->getPos().Z+m_colliding[i]->getSize().Z-50)
                {
                    if(m_type!="wall" && m_position.Z>5)//ground or walls shouldnt break
                        m_life=0;
                }
            }
            else if(m_colliding[i]->getType()=="block")
            {
                if(m_colliding[i]->getPos().Z+m_colliding[i]->getSize().Z*2<=m_position.Z)
                {
                    m_onTopOf=m_colliding[i];

                    if(!wasOnTop)//landing -> stop Z velocity
                        m_velocity.Z=0;
                    //m_onTopOf->setVisible(false);
                }
            }
        }
        m_colliding.clear();
    }
}

void Object::moveToDir()
{
    //m_position+=m_direction*m_speed*ft;
    m_velocity=m_direction*m_speed*ft;
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
    if(m_physical && m_gravity)
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
        m_position.X+=m_velocity.X+m_movementVelocity.X;
    if(y)
        m_position.Y+=m_velocity.Y+m_movementVelocity.Y;
    /*if(x)
        m_position.X+=m_velocity.X;
    if(y)
        m_position.Y+=m_velocity.Y;*/
    /*if(x)
        m_position.X+=m_velocity.X*m_movementVelocity.X;
    if(y)
        m_position.Y+=m_velocity.Y*m_movementVelocity.Y;*/


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
bool Object::collidedWithHookable()
{
    for(unsigned int i=0,count=m_colliding.size();i<count;i++)
    {
        if(m_colliding[i]->isHookable())
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


bool Object::onGround()
{
    return m_onTopOf!=NULL;
}




string Object::writeObj()
{

    std::ostringstream oss;

    //classe
    oss << "@ " << m_type << ":";

    //x
    if(m_position.X!=0)
        oss<<" x: " << m_position.X;

    //y
    if(m_position.Y!=0)
        oss<<" y: " << m_position.Y;

    //z
    if(m_position.Z!=0)
        oss<<" z: " << m_position.Z;

    //taille
    if(m_size.X==m_size.Y && m_size.X==m_size.Z)
        oss<<" t: " << m_size.X;
    else
    {
        if(m_size.X!=0.5)
            oss << " tx: " << m_size.X;
        if(m_size.Y!=0.5)
            oss << " ty: " << m_size.Y;
        if(m_size.Z!=0.5)
            oss << " tz: " << m_size.Z;
    }
    //texture
    if(m_texture!=NULL)
        oss<<" text: " << m_texture->getChemin();

    return oss.str();
}


void Object::readObj(ifstream* fichier1)
{
    std::string befor_read="",read_name_before="";
    std::string cur_read="";
    double cur_double=0;

    int maxIteration=1000;

    while(befor_read!="@" && maxIteration>0)
    {
        maxIteration--;
        if(read_name_before=="x")
            *fichier1 >> m_position.X;
        else if(read_name_before=="y")
            *fichier1 >> m_position.Y;
        else if(read_name_before=="z")
            *fichier1 >> m_position.Z;
        else if(read_name_before=="t")
        {
            *fichier1 >> cur_double;
            setSize(Vector3D(cur_double,cur_double,cur_double));
        }
        else if(read_name_before=="tx")
        {
            *fichier1 >> cur_double;
            m_size.X=cur_double;
            if(m_type=="rock")
                setSize(Vector3D(m_size.X,m_size.X,m_size.X));
            else if(m_type=="cylindre")
                setSize(Vector3D(m_size.X,m_size.X,m_size.Z));
            else if(m_type=="cone")
                setSize(Vector3D(m_size.X,m_size.X,m_size.Z));
            setSize(Vector3D(m_size.X,m_size.Y,m_size.Z));
        }
        else if(read_name_before=="ty")
        {
            *fichier1 >> m_size.Y;
            setSize(Vector3D(m_size.X,m_size.Y,m_size.Z));
        }
        else if(read_name_before=="tz")
        {
            *fichier1 >> m_size.Z;
            setSize(Vector3D(m_size.X,m_size.Y,m_size.Z));
        }
        else if(read_name_before=="text")
        {
            *fichier1 >> cur_read;
            GTexture::getInstance()->addTexture(cur_read);
            setTexture(GTexture::getInstance()->getTexture(cur_read));
        }
        else if(read_name_before=="name")
        {
            *fichier1 >> m_name;
        }

        *fichier1 >> cur_read;
        befor_read=cur_read;
        read_name_before=befor_read.substr(0,befor_read.size()-1);//enleve le ":"
    }
}







