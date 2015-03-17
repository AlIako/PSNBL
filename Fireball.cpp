#include "Fireball.h"

Fireball::Fireball()
{
    m_type="projectile";
    m_name="fireball";
    m_speed=1;
    m_gravity=false;

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
        m_life=0;
        Effects::getInstance()->addExplosion(m_position);

        for(unsigned int i=0;i<m_colliding.size();i++)
        {
            m_colliding[i]->loseLife(1);
        }
    }
}

void Fireball::draw()
{
    if(m_visible)
    {
        if(m_texture!=NULL)
            m_texture->bind();

        glPushMatrix();
        glTranslated(m_position.X,m_position.Y,m_position.Z+m_size.Z/2);
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
    }
}
