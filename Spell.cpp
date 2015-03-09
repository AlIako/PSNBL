#include "Spell.h"
/*
lanceur de disque: destroy friends' ropes
long jump shift+space
run (require energy)
*/


Spell::Spell()
{
    m_required="nothing";
    m_name="spell";
    m_cooldown=1000;
    m_lastCast.reset();

    m_icon=NULL;
    m_position=Vector3D(0.9,0.2,0);
    m_size=Vector3D(0.05,0.05,0);
}

void Spell::ini()
{
    if(m_icon==NULL)
    {
        string path="../data/textures/spells/"+m_name+".png";
        GTexture::getInstance()->addTexture(path);
        m_icon=GTexture::getInstance()->getTexture(path);
    }
}

void Spell::update(double functionTime)
{
    //if(m_icon==NULL)//fail init?
    //    ini();
}

void Spell::draw()
{
    Video::getInstance()->matrixOrtho2D();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);


    if(m_icon)
        m_icon->bind();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    m_lastCast.couler();
    double clarity=(m_lastCast.timePast()/(double)m_cooldown);
    if(m_lastCast.ecouler(m_cooldown))
        clarity=1;

    glColor4ub(clarity*255,clarity*255,clarity*255,255);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);    glVertex2d(m_position.X,m_position.Y);
        glTexCoord2d(0,1);    glVertex2d(m_position.X,m_position.Y+m_size.Y);
        glTexCoord2d(1,1);    glVertex2d(m_position.X+m_size.X,m_position.Y+m_size.Y);
        glTexCoord2d(1,0);    glVertex2d(m_position.X+m_size.X,m_position.Y);
    glEnd();

    glDisable(GL_BLEND);

    glEnable(GL_DEPTH_TEST);
    Video::getInstance()->matrixProjection();
}

bool Spell::cast()
{
    m_lastCast.couler();
    if(m_lastCast.ecouler(m_cooldown))
    {
        m_lastCast.reset();
        return true;
    }
    return false;
}



int Spell::nameToId(string name)
{
    if(name=="jump")
        return 1;
    if(name=="longjump")
        return 2;
    if(name=="rope")
        return 3;
    return 0;
}
string Spell::idToName(int id)
{
    if(id==1)
        return "jump";
    if(id==2)
        return "longjump";
    if(id==3)
        return "rope";
    return "spell";
}

