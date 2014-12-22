#include "Player.h"




Player::Player()
{
    m_texture=NULL;
    m_position.X=0;
    m_position.Y=0;
    m_position.Z=20;

    m_rotation.Z=0;

    m_pressed[UP]=false;
    m_pressed[DOWN]=false;
    m_pressed[LEFT]=false;
    m_pressed[RIGHT]=false;

    m_speed=0.5;
}





void Player::ini()
{
    if(gtext!=NULL)
    {
        gtext->addTexture("../data/textures/char1.png");
        m_texture=gtext->getTexture("../data/textures/char1.png");
    }
}

void Player::draw()
{

    glColor3ub(255,255,255);



    glPushMatrix();
    glTranslated(m_position.X,m_position.Y,m_position.Z-5);
    glRotated(m_rotation.Z,0,0,1);
    if(m_texture!=NULL)
        m_texture->bind();

    double m_lx=1;
    double m_ly=1;
    double m_lz=1;

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

void Player::pressKey(DIRECTION k, bool pressed)
{
    m_pressed[k]=pressed;
    cerr<<"press key"<<endl;
}

void Player::move()
{
    m_direction.write();
    if(m_pressed[UP])
    {
        m_position.X+=m_speed*m_direction.X;
        m_position.Y+=m_speed*m_direction.Y;
        m_position.Z+=m_speed*m_direction.Z;
    }
    if(m_pressed[DOWN])
    {
        m_position.X-=m_speed*m_direction.X;
        m_position.Y-=m_speed*m_direction.Y;
        m_position.Z-=m_speed*m_direction.Z;
    }
    if(m_pressed[RIGHT])
    {
        m_position.X+=m_direction.Y*m_speed;
        m_position.Y-=m_direction.X*m_speed;
    }
    if(m_pressed[LEFT])
    {
        m_position.X-=m_direction.Y*m_speed;
        m_position.Y+=m_direction.X*m_speed;

    }
}


