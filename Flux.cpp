#include "Flux.h"



Flux::Flux()
{
    m_name="flux";
    m_type="flux";

    m_size=Vector3D(3,3,5);

    zOffset=0;
    goingUp=true;
}




void Flux::ini()
{
    string path="../data/textures/carpet_red.jpg";
    m_hookable=false;
    m_block=false;

    char* tempPath=stringtochar(path);
    GTexture::getInstance()->addTexture(tempPath);
    m_texture=GTexture::getInstance()->getTexture(tempPath);
    delete tempPath;


    m_speed=0.1;
    m_transparency=true;
}




void Flux::update(double functionTime)
{
    m_rotation.Z+=functionTime;


    if(goingUp)
    {
        zOffset+=functionTime*m_speed;

        if(zOffset>=m_size.Z*2-m_size.Z*0.6)
            goingUp=false;
    }
    else
    {
        zOffset-=functionTime*m_speed;


        if(zOffset<=0)
            goingUp=true;
    }
}




void Flux::draw()
{
    if(m_visible)
    {
        glDisable(GL_LIGHTING);


        //m_size=Vector3D(3,3,5);
        glColor4ub(255,255,255,255);

        if(m_texture!=NULL)
            m_texture->bind();

        glPushMatrix();
        glTranslated(m_position.X,m_position.Y,m_position.Z);


        glDisable(GL_LIGHTING);
        glTranslated(0,0,m_size.Z*2*0);
        glDisable(GL_CULL_FACE);
        m_texture->bind();
        glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        glEnable(GL_BLEND);
        GLUquadric* params = gluNewQuadric();
        gluQuadricTexture(params,GL_TRUE);

        glRotated(m_rotation.Z-180,0,0,1);

        gluCylinder(params,m_size.X*1,m_size.X*1,m_size.Z*2,5,5);


        glRotated(-2*m_rotation.Z,0,0,1);
        glTranslated(0,0,zOffset);

        gluCylinder(params,m_size.X*1.2,m_size.X*1.2,m_size.Z*0.6,5,5);

        m_rotation.Z+=ft;
        gluDeleteQuadric(params);

        glDisable(GL_BLEND);


        glPopMatrix();

    }
}

