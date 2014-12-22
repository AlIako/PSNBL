#include "Personnage.h"

Personnage::Personnage()
{
    loadSprite();
    m_position.X=0.5;
    m_position.Y=0.5;
    m_rotation.Z=90;
    calculDirector();


    speed=5;



    m_pressed[UP]=false;
    m_pressed[DOWN]=false;
    m_pressed[LEFT]=false;
    m_pressed[RIGHT]=false;
}

void Personnage::ini()
{

}


void Personnage::loadSprite()
{
    if(gtext!=NULL)
    {
        gtext->addTexture("data/char1.png");
        m_texture=gtext->getTexture("data/char1.png");
    }
}


void Personnage::draw()
{
    glColor3ub(255,255,255);



    glPushMatrix();
    glTranslated(m_position.X,m_position.Y,-700);
    glRotated(m_rotation.Z,0,0,1);
    if(m_texture!=NULL)
        m_texture->bind();

    double m_lx=40;
    double m_ly=40;
    double m_lz=40;

    glBegin(GL_QUADS);
    glTexCoord2d(0,1);     glVertex3d(m_lx,m_ly,m_lz);
    glTexCoord2d(0,0);     glVertex3d(m_lx,m_ly,-m_lz);
    glTexCoord2d(1,0);     glVertex3d(-m_lx,m_ly,-m_lz);
    glTexCoord2d(1,1);     glVertex3d(-m_lx,m_ly,m_lz);

    glTexCoord2d(0,1);     glVertex3d(m_lx,-m_ly,m_lz);
    glTexCoord2d(0,0);     glVertex3d(m_lx,-m_ly,-m_lz);
    glTexCoord2d(1,0);     glVertex3d(m_lx,m_ly,-m_lz);
    glTexCoord2d(1,1);     glVertex3d(m_lx,m_ly,m_lz);

    glTexCoord2d(0,1);     glVertex3d(-m_lx,-m_ly,m_lz);
    glTexCoord2d(0,0);     glVertex3d(-m_lx,-m_ly,-m_lz);
    glTexCoord2d(1,0);     glVertex3d(m_lx,-m_ly,-m_lz);
    glTexCoord2d(1,1);     glVertex3d(m_lx,-m_ly,m_lz);

    glTexCoord2d(0,1);     glVertex3d(-m_lx,m_ly,m_lz);
    glTexCoord2d(0,0);     glVertex3d(-m_lx,m_ly,-m_lz);
    glTexCoord2d(1,0);     glVertex3d(-m_lx,-m_ly,-m_lz);
    glTexCoord2d(1,1);     glVertex3d(-m_lx,-m_ly,m_lz);

    glTexCoord2d(0,1);     glVertex3d(m_lx,m_ly,m_lz);
    glTexCoord2d(0,0);     glVertex3d(-m_lx,m_ly,m_lz);
    glTexCoord2d(1,0);     glVertex3d(-m_lx,-m_ly,m_lz);
    glTexCoord2d(1,1);     glVertex3d(m_lx,-m_ly,m_lz);

    glTexCoord2d(0,1);     glVertex3d(m_lx,m_ly,-m_lz);
    glTexCoord2d(0,0);     glVertex3d(-m_lx,m_ly,-m_lz);
    glTexCoord2d(1,0);     glVertex3d(-m_lx,-m_ly,-m_lz);
    glTexCoord2d(1,1);     glVertex3d(m_lx,-m_ly,-m_lz);

    glEnd();

    glTranslated(-m_position.X,-m_position.Y,0);
    glPopMatrix();

}


void Personnage::pressKey(DIRECTION k, bool pressed)
{
    m_pressed[k]=pressed;
}

void Personnage::handlePressedKeys()
{
    if(m_pressed[UP])
        move(1);
    if(m_pressed[DOWN])
        move(-1);


    if(m_pressed[RIGHT])
        addAngle(-3);
    if(m_pressed[LEFT])
        addAngle(3);
}


void Personnage::move(int step)
{
    m_position.X+=speed*step*m_dx;
    m_position.Y+=speed*step*m_dy;
}



void Personnage::calculDirector()
{

    double rad=m_rotation.Z*3.14/180;
    m_dx=cos(rad);
    m_dy=sin(rad);
}
void Personnage::addAngle(int a)
{
    m_rotation.Z+=a;

    calculDirector();
}

Personnage::~Personnage()
{
    //dtor
}
