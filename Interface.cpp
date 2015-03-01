#include "Interface.h"


Interface::Interface()
{
    m_target=NULL;
}


void Interface::ini()
{
    m_font.init("../data/fonts/arial.TTF", 16);

    m_lifebar.ini();
    m_crosshair.ini();

    m_playerName.ini(Video::getInstance()->getWidth(),Video::getInstance()->getHeight(),&m_font);
    m_playerName.setX(0.05);
    m_playerName.setY(0.92);

    m_fps.ini(Video::getInstance()->getWidth(),Video::getInstance()->getHeight(),&m_font);
    m_fps.setX(0.85);
    m_fps.setY(0.92);
}


void Interface::draw()
{
    if(m_mode=="play")
        m_crosshair.draw();

    m_lifebar.draw();
    m_playerName.draw(255,255,255);
    m_fps.draw(255,255,255);
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
    m_crosshair.update(functionTime);

    m_lifebar.update(functionTime,m_target);

    if(m_target!=NULL)
    {
        std::ostringstream oss;
        if(m_mode=="spectate")
            oss << "Spectating: ";
        oss << m_target->getOnlineName();

        m_playerName.setTexte(oss.str());
    }

}


void Interface::setFPS(int fps)
{
    std::ostringstream oss;
    oss << "FPS: ";
    oss << fps;
    m_fps.setTexte(oss.str());
}


