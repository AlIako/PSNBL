#include "Fade.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>




Fade::Fade()
{
}



void Fade::ini()
{
    m_r=0;
    m_g=0;
    m_b=0;
    m_alpha=1;

    m_fading=false;
    m_fadingIn=false;
}



void Fade::draw()
{
    if(m_alpha>0)
    {
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);


        glBindTexture(GL_TEXTURE_2D,0);
        GTexture::getInstance()->setLastBind(NULL);

        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glColor4ub(m_r,m_g,m_b,m_alpha*255);

        glBegin(GL_QUADS);
            glTexCoord2d(1,0);    glVertex2d(0,0);
            glTexCoord2d(1,1);    glVertex2d(0,1);
            glTexCoord2d(0,1);    glVertex2d(1,1);
            glTexCoord2d(0,0);    glVertex2d(1,0);
        glEnd();


        glDisable(GL_BLEND);




        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);


        glColor4ub(255,255,255,255);
    }
}


void Fade::update(double functionTime)
{
    if(m_fading)
    {
        double factor=0.1;


        if(m_fadingIn)
        {
            m_alpha+=functionTime*factor;

            if(m_alpha>=1)
            {
                m_fading=false;
                m_alpha=1;
            }
        }
        else//fading out
        {
            m_alpha-=functionTime*factor;

            if(m_alpha<=0)
            {
                m_fading=false;
                m_alpha=0;
            }
        }
    }
}


void Fade::startFadeIn()
{
    m_fading=true;
    m_fadingIn=true;
}


void Fade::startFadeOut()
{
    m_fading=true;
    m_fadingIn=false;
}




