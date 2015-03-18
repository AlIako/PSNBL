#include "Explosion.h"


Explosion::Explosion()
{
    m_size=Vector3D(1,1,1);
}

void Explosion::ini()
{
    GTexture::getInstance()->addTexture("../data/textures/fire.jpg");
    m_texture=GTexture::getInstance()->getTexture("../data/textures/fire.jpg");

    start();
}

void Explosion::start()
{
    m_over=false;
    m_speed=1;
    m_time=300;
    particles.clear();
    particle cur_p;
    cur_p.life=2.0;
    cur_p.position=Vector3D(0,0,0);
    cur_p.speed=Vector3D(0,0,0);
    cur_p.direction=Vector3D(0,0,0);
    cur_p.rotation=Vector3D(0,0,0);

    double sizeP=0.5;

    for(unsigned int i=0;i<100;i++)
    {
        if(m_size.X>=0.01)
            cur_p.position=Vector3D(myDoubleRand(0,m_size.X)-m_size.X/2,myDoubleRand(0,m_size.Y)-m_size.Y/2,myDoubleRand(0,m_size.Z)-m_size.Z/2);
        else cur_p.position=Vector3D(m_size.X,m_size.Y,m_size.Z);

        /*if(vitesse>=0.1)
            cur_p.vitesse=Vector3D(myDoubleRand(0,vitesse*2)-vitesse,myDoubleRand(0,vitesse*2)-vitesse,myDoubleRand(0,vitesse*2)-vitesse);
        else cur_p.vitesse=Vector3D(vitesse,vitesse,vitesse);*/
        int tempVit=floor(m_speed*1000);
        cur_p.speed=Vector3D(myIntRand(0,tempVit*2)-tempVit,myIntRand(0,tempVit*2)-tempVit,myIntRand(0,tempVit*2)-tempVit)/1000.0;

        cur_p.direction=Vector3D(myDoubleRand(-1,1),myDoubleRand(-1,1),myDoubleRand(-1,1)).normalize();
        cur_p.rotation=Vector3D(myDoubleRand(-180,180),myDoubleRand(-180,180),myDoubleRand(-180,180));
        cur_p.life=myDoubleRand(1.0,1.3);

        if(sizeP>=0.1 && 0)
            cur_p.size=myDoubleRand(sizeP,sizeP*3);
        else cur_p.size=sizeP;

        particles.push_back(cur_p);
    }

}

void Explosion::update(double functionTime)
{
    bool onealive=false;
    for(unsigned int i=0;i<particles.size();i++)
    {
        particles[i].position+=functionTime*particles[i].direction*particles[i].speed/5;
        particles[i].life-=functionTime*20.00/m_time;
        if(particles[i].life>0)
            onealive=true;
    }
    if(!onealive)
    {
        particles.clear();
        m_over=true;
    }
}

void Explosion::draw()
{
    if(m_texture!=NULL)
        m_texture->bind();

    //glAlphaFunc(GL_GREATER,0.1f);
    //glEnable(GL_ALPHA_TEST);
    glDisable(GL_CULL_FACE);
    Lighting::getInstance()->glDisableLighting();

    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glEnable(GL_BLEND);


    glPushMatrix();
    glTranslated(m_position.X,m_position.Y,m_position.Z+m_size.Z*0);
    for(unsigned int i=0;i<particles.size();i++)
    {
        if(particles[i].life>0)
        {
            if(particles[i].life>0.7)
                glColor4f(1.0, 1.0, 1.0, 0.7);
            else
                glColor4f(1.0, 1.0, 1.0, particles[i].life);

            glTranslated(particles[i].position.X,particles[i].position.Y,particles[i].position.Z);
            glRotated(particles[i].rotation.X,1,0,0);
            glRotated(particles[i].rotation.Y,0,1,0);
            glRotated(particles[i].rotation.Z,0,0,1);

            glBegin(GL_TRIANGLES);
            glTexCoord2d(1,0);      glVertex3d(0,0,0);
            glTexCoord2d(0,0);      glVertex3d(particles[i].size,particles[i].size,0);
            glTexCoord2d(0.5,1);      glVertex3d(particles[i].size/2,particles[i].size/2,particles[i].size);
            glEnd();

            glRotated(-particles[i].rotation.Z,0,0,1);
            glRotated(-particles[i].rotation.Y,0,1,0);
            glRotated(-particles[i].rotation.X,1,0,0);
            glTranslated(-particles[i].position.X,-particles[i].position.Y,-particles[i].position.Z);
        }
    }

    glDisable(GL_BLEND);
    glPopMatrix();

    //glEnable(GL_CULL_FACE);
    glDisable(GL_ALPHA_TEST);
    //glEnable(GL_LIGHTING);

}

