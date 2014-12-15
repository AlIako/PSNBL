#include "Personnage.h"

Personnage::Personnage()
{
    loadSprite();
    m_x=0.5;
    m_y=0.5;
    m_angle=90;
    calculDirector();


    speed=5;



    m_pressed[UP]=false;
    m_pressed[DOWN]=false;
    m_pressed[LEFT]=false;
    m_pressed[RIGHT]=false;
}

void Personnage::loadSprite()
{
    m_texture=loadTexture("data/char1.png");
}


void Personnage::draw()
{
    glColor3ub(255,255,255);



    glPushMatrix();
    glTranslated(m_x,m_y,-700);
    glRotated(m_angle,0,0,1);
    glBindTexture(GL_TEXTURE_2D,m_texture);

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

    glTranslated(-m_x,-m_y,0);
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
    m_x+=speed*step*m_dx;
    m_y+=speed*step*m_dy;
}



void Personnage::calculDirector()
{

    double rad=m_angle*3.14/180;
    m_dx=cos(rad);
    m_dy=sin(rad);
}
void Personnage::addAngle(int a)
{
    m_angle+=a;

    calculDirector();
}

Personnage::~Personnage()
{
    //dtor
}
