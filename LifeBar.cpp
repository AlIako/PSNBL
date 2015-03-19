#include "LifeBar.h"

LifeBar::LifeBar()
{
    m_currentLife=50;
    m_maxLife=100;
    m_texture=NULL;

    m_barWidth=0.6;
    m_barHeight=0.05;

    m_position=Vector3D(0.2,0.1,0);
    m_color=Vector3D(255,0,0);
}

void LifeBar::ini()
{

}

void LifeBar::draw()
{

    Video::getInstance()->matrixOrtho2D();

    Lighting::getInstance()->glDisableLighting();
    glDisable(GL_TEXTURE_2D);


    //filled
    double tempWidth=m_barWidth*(m_currentLife/m_maxLife);
    if(m_currentLife<=0)
        tempWidth=0;

    glColor4ub(m_color.X,m_color.Y,m_color.Z,255);
    glBegin(GL_QUADS);
        glTexCoord2d(1,0);    glVertex2d(m_position.X,m_position.Y);
        glTexCoord2d(1,1);    glVertex2d(m_position.X,m_position.Y+m_barHeight);
        glTexCoord2d(0,1);    glVertex2d(m_position.X+tempWidth,m_position.Y+m_barHeight);
        glTexCoord2d(0,0);    glVertex2d(m_position.X+tempWidth,m_position.Y);
    glEnd();

    //rest
    glColor4ub(0,0,0,255);
    glBegin(GL_QUADS);
        glTexCoord2d(1,0);    glVertex2d(m_position.X+tempWidth,m_position.Y);
        glTexCoord2d(1,1);    glVertex2d(m_position.X+tempWidth,m_position.Y+m_barHeight);
        glTexCoord2d(0,1);    glVertex2d(m_position.X+m_barWidth,m_position.Y+m_barHeight);
        glTexCoord2d(0,0);    glVertex2d(m_position.X+m_barWidth,m_position.Y);
    glEnd();



    glEnable(GL_TEXTURE_2D);

    Video::getInstance()->matrixProjection();
}


void LifeBar::update(double functionTime, Object* o)
{
    if(o!=NULL)
    {
        m_currentLife=o->getLife();
        m_maxLife=o->getLifeMax();
    }
}
