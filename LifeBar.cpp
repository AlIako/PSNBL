#include "LifeBar.h"

LifeBar::LifeBar()
{
    m_currentLife=50;
    m_maxLife=100;
    m_texture=NULL;

    m_barWidth=0.6;
    m_barHeight=0.05;
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

    glColor4ub(255,0,0,255);
    glBegin(GL_QUADS);
        glTexCoord2d(1,0);    glVertex2d(0.2,0.1);
        glTexCoord2d(1,1);    glVertex2d(0.2,0.1+m_barHeight);
        glTexCoord2d(0,1);    glVertex2d(0.2+tempWidth,0.1+m_barHeight);
        glTexCoord2d(0,0);    glVertex2d(0.2+tempWidth,0.1);
    glEnd();

    //rest
    glColor4ub(0,0,0,255);
    glBegin(GL_QUADS);
        glTexCoord2d(1,0);    glVertex2d(0.2+tempWidth,0.1);
        glTexCoord2d(1,1);    glVertex2d(0.2+tempWidth,0.1+m_barHeight);
        glTexCoord2d(0,1);    glVertex2d(0.2+m_barWidth,0.1+m_barHeight);
        glTexCoord2d(0,0);    glVertex2d(0.2+m_barWidth,0.1);
    glEnd();



    glEnable(GL_TEXTURE_2D);

    Video::getInstance()->matrixProjection();
}


void LifeBar::update(double functionTime, Player* p)
{
    if(p!=NULL)
    {
        m_currentLife=p->getLife();
        m_maxLife=p->getLifeMax();
    }
}
