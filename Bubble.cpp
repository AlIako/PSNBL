#include "Bubble.h"



Bubble::Bubble()
{
    m_life=0;
    m_texture=NULL;
    m_size=Vector3D(1,1,1);
    goingUp=false;
}


void Bubble::ini()
{
    m_type="bubble";

    zUp=0;

    m_life=1.0;
    m_speed=myIntRand(1,5)/200.0;

    Object::ini();
}


void Bubble::draw()
{
    if(m_texture!=NULL)
        m_texture->bind();


    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);

    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glColor4f(1.0, 1.0, 1.0, m_life);
    glTranslated(m_position.X,m_position.Y,m_position.Z+zUp);

    GLUquadric* params = gluNewQuadric();
    gluQuadricTexture(params,GL_TRUE);

    gluSphere(params,m_size.X,10,10);

    gluDeleteQuadric(params);

    glColor4f(1.0, 1.0, 1.0, 1.0);

    glTranslated(-m_position.X,-m_position.Y,-m_position.Z-zUp);

    glDisable(GL_BLEND);

}






void Bubble::update(double functionTime)
{
    if(m_life>0)
    {
        m_life-=functionTime*speedDie;
        m_size.X+=functionTime*speedSize;

        if(goingUp)
            zUp+=functionTime*m_speed;
    }
}



