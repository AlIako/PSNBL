#include "Player.h"
#define MAPSIZE 50




Player::Player()
{
    m_texture=NULL;
    m_position=Vector3D(-MAPSIZE/1.5,-MAPSIZE/1.5,20);

    m_rotation.Z=0;

    m_pressed[UP]=false;
    m_pressed[DOWN]=false;
    m_pressed[LEFT]=false;
    m_pressed[RIGHT]=false;

    m_physical=true;
    m_destructible=true;

    m_type="player";
}


void Player::linkRope(Rope* p)
{
    m_rope=p;
}


void Player::ini()
{
//    getgt.get();
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
    glTranslated(m_position.X,m_position.Y,m_position.Z+1);
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
    //m_direction.write();

    if(m_pressed[UP])
    {
        m_velocity.X+=m_speed*m_direction.X*ft;
        m_velocity.Y+=m_speed*m_direction.Y*ft;
        //m_position.Z+=m_speed*m_direction.Z;
    }
    if(m_pressed[DOWN])
    {
        m_velocity.X-=m_speed*m_direction.X*ft;
        m_velocity.Y-=m_speed*m_direction.Y*ft;
        //m_position.Z-=m_speed*m_direction.Z;
    }
    if(m_pressed[RIGHT])
    {
        m_velocity.X+=m_direction.Y*m_speed*ft;
        m_velocity.Y-=m_direction.X*m_speed*ft;
    }
    if(m_pressed[LEFT])
    {
        m_velocity.X-=m_direction.Y*m_speed*ft;
        m_velocity.Y+=m_direction.X*m_speed*ft;

    }

    double maxspeed=0.1;

    //speed limit
    if(m_velocity.X>maxspeed)
        m_velocity.X=maxspeed;
    else if(m_velocity.X<-maxspeed)
        m_velocity.X=-maxspeed;

    if(m_velocity.Y>maxspeed)
        m_velocity.Y=maxspeed;
    else if(m_velocity.Y<-maxspeed)
        m_velocity.Y=-maxspeed;

    double friction=0.002;

    //friction
    if(m_velocity.X>0)
        m_velocity.X-=ft*friction;
    else
        m_velocity.X+=ft*friction;

    if(abs(m_velocity.X)<=ft*friction)
        m_velocity.X=0;


    if(m_velocity.Y>0)
        m_velocity.Y-=ft*friction;
    else
        m_velocity.Y+=ft*friction;

    if(abs(m_velocity.Y)<=ft*friction)
        m_velocity.Y=0;
}


void Player::resurrect()
{
    Object::resurrect();
    m_position=Vector3D(-MAPSIZE/1.5,-MAPSIZE/1.5,20);
}





