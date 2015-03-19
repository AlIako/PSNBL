#include "Fireball.h"
#include "Map.h"
#include "Damage.h"

Fireball::Fireball()
{
    m_type="projectile";
    m_name="fireball";
    m_speed=1;
    m_gravity=false;
    m_block=false;
    m_life=1;

    m_texture_fire=NULL;
}




void Fireball::ini()
{
    m_texture=GTexture::getInstance()->addGetTexture("../data/textures/bedrock.png");
    m_texture_fire=GTexture::getInstance()->addGetTexture("../data/textures/fire.jpg");
}
void Fireball::update(double functionTime)
{
    ft=functionTime;
    moveToDir();
    m_rotation.X+=ft;
    m_rotation.Y+=ft;
    m_rotation.Z+=ft;

    if(m_collided)
    {
        if(!collidedWithType("boss"))
            action(0,NULL);
    }
}

void Fireball::action(int type,Object* o)
{
    if(type==0)
    {
        m_life=0;

        //create damage
        Damage* td=new Damage();
        td->setSize(m_size*1.5);
        td->setSize(Vector3D(5,5,5));
        td->setPos(m_position-Vector3D(0,0,5));
        td->setDamageValue(10);
        td->setDamageType(3);
        td->ini();

        Map::getInstance()->getObjects()->push_back(td);
    }
}

void Fireball::draw()
{
    if(m_visible)
    {

        Lighting::getInstance()->glDisableLighting();

        if(m_texture!=NULL)
            m_texture->bind();

        glPushMatrix();
        glTranslated(m_position.X,m_position.Y,m_position.Z);
        glRotated(m_rotation.X,1,0,0);
        glRotated(m_rotation.Y,0,1,0);
        glRotated(m_rotation.Z,0,0,1);

        GLUquadric* params = gluNewQuadric();
        gluQuadricTexture(params,GL_TRUE);

        gluSphere(params,m_size.X+m_size.X/2,5,5);


        //fire
        if(m_texture_fire!=NULL)
            m_texture_fire->bind();

        glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        glEnable(GL_BLEND);

        glRotated(-2*m_rotation.X,1,0,0);
        glRotated(-2*m_rotation.Y,0,1,0);
        glRotated(-2*m_rotation.Z,0,0,1);
        gluSphere(params,m_size.X+m_size.X,5,5);

        gluDeleteQuadric(params);

        glPopMatrix();

        glDisable(GL_BLEND);
        Lighting::getInstance()->glEnableLighting();
    }
}
