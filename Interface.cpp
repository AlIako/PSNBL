#include "Interface.h"


Interface* Interface::m_instance = new Interface();


Interface* Interface::getInstance()
{
    return m_instance;
}



Interface::Interface()
{
    m_target=NULL;
    m_targetBoss=NULL;
    initalized=false;
}


void Interface::ini()
{
    if(!initalized)
    {
        initalized=true;

        m_font.init("../data/fonts/arial.TTF", 16);

        m_lifebar.ini();
        m_crosshair.ini();

        m_lifebarBoss.ini();
        m_lifebarBoss.setPos(m_lifebarBoss.getPos()+Vector3D(0,0.1,0));
        m_lifebarBoss.setColor(Vector3D(255,255,0));

        m_playerName.ini(Video::getInstance()->getWidth(),Video::getInstance()->getHeight(),&m_font);
        m_playerName.setX(0.05);
        m_playerName.setY(0.92);

        m_fps.ini(Video::getInstance()->getWidth(),Video::getInstance()->getHeight(),&m_font);
        m_fps.setX(0.85);
        m_fps.setY(0.92);

        m_warningLava.setPos(Vector3D(0.3,0.35,0));
        m_warningLava.setSize(Vector3D(0.4,0.3,0));
        m_warningLava.setName("warning");
        m_warningLava.setTexture(GTexture::getInstance()->addGetTexture("../data/textures/interface/warning.png"));
        m_warningLava.ini();
        m_warningLava.setAlpha(0);
    }
}


void Interface::draw()
{
    if(m_mode=="play")
        m_crosshair.draw();

    m_lifebar.draw();
    m_playerName.draw(255,255,255);
    m_fps.draw(255,255,255);

    //spells
    if(m_target!=NULL)
    {
        vector<Spell*>* s=m_target->getSpells();
        for(unsigned int i=0;i<s->size();i++)
        {
            (*s)[i]->draw();
        }
    }

    //warning
    if(m_warningLava.getAlpha()>0)
        m_warningLava.draw();

    //boss
    if(m_targetBoss)
    {
        m_lifebarBoss.draw();
    }
}

void Interface::warningLava()
{
    time_since_warning.reset();
    m_warningLava.setAlpha(0);
    m_warning=true;
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

    //warning lava
    time_since_warning.couler();
    double curAlpha=m_warningLava.getAlpha();
    if(m_warning && time_since_warning.timePast()<3000)
    {
        m_warningLava.setAlpha(curAlpha+functionTime/10);
        if(m_warningLava.getAlpha()>1)
            m_warningLava.setAlpha(1);
    }
    else
    {
        m_warning=false;
        m_warningLava.setAlpha(curAlpha-functionTime/10);
        if(m_warningLava.getAlpha()<0)
        {
            m_warningLava.setAlpha(0);
        }
    }

    //boss
    if(m_targetBoss)
        m_lifebarBoss.update(functionTime,m_targetBoss);

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
    Lighting::getInstance()->glDisableLighting();

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
    Lighting::getInstance()->glEnableLighting();
}



void Interface::setFPS(int fps)
{
    std::ostringstream oss;
    oss << "FPS: ";
    oss << fps;
    m_fps.setTexte(oss.str());
}


void Interface::close()
{
    m_target=NULL;
    m_targetBoss=NULL;
}


