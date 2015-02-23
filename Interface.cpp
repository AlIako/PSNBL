#include "Interface.h"


Interface::Interface()
{
    m_target=NULL;
}


void Interface::ini()
{
    m_lifebar.ini();
}


void Interface::draw()
{
    m_lifebar.draw();
}

void Interface::drawScreenEffect(std::string path)
{
    int r=155;
    int g=155;
    int b=155;
    if(path=="../data/textures/lava.png")
    {
        r=255;
        g=153;
        b=0;
    }

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    Video::getInstance()->matrixOrtho2D();

    /*if(m_texture!=NULL)
        m_texture->bind(true);*/
    glBindTexture(GL_TEXTURE_2D,0);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glColor4ub(r,g,b,100);

    glBegin(GL_QUADS);
        glTexCoord2d(1,0);    glVertex2d(0,0);
        glTexCoord2d(1,1);    glVertex2d(0,1);
        glTexCoord2d(0,1);    glVertex2d(1,1);
        glTexCoord2d(0,0);    glVertex2d(1,0);
    glEnd();


    glDisable(GL_BLEND);

    Video::getInstance()->matrixProjection();



    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void Interface::update(double functionTime)
{
    m_lifebar.update(functionTime,m_target);
}

