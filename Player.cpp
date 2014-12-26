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
    m_pressed[KEY_E]=false;

    m_physical=true;
    m_destructible=true;

    m_rope=NULL;
    m_type="player";

    m_jumping=false;
}

void Player::update(double functionTime)
{
    if(m_collided)
    {
        m_jumping=false;
        m_collided=false;
    }

    if(hookedToRope())
    {
        if(m_rope->getLife()==0)
            unlinkRope();

        if(ropeHooked())
        {
            m_jumping=false;
            m_rope->pullMe(this);
        }
    }

    Object::update(functionTime);
}
void Player::jump()
{
    if(!m_jumping && (abs(m_velocity.Z)<0.1 || ropeHooked()))
    {
        m_jumping=true;

        if(m_velocity.Z<0.4)
            setVel(Vector3D(getVel().X,getVel().Y,0.4));

        unlinkRope();
    }
}

void Player::pullUpRope()
{
    if(hookedToRope() && ropeHooked())
    {
        m_rope->pullUp();
    }
}

void Player::linkRope(Rope* p)
{
    m_jumping=false;

    unlinkRope();

    m_rope=p;
    m_rope->linkToObject(this);
}
void Player::unlinkRope()
{
    if(m_rope!=NULL)
        m_rope->unlink();
    m_rope=NULL;
}

bool Player::hookedToRope()
{
    return m_rope!=NULL;
}

bool Player::ropeHooked()
{
    if(hookedToRope())
        if(m_rope->isHooked())
            return true;
    return false;
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
    cerr<<"press "<< k <<" key"<<endl;
}

void Player::resurrect()
{
    Object::resurrect();
    m_position=Vector3D(-MAPSIZE/1.5,-MAPSIZE/1.5,20);

    unlinkRope();
}


void Player::move()
{
    //m_direction.write();

    if(ropeHooked())
        m_speed*=2;

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

    //hook
    if(m_pressed[KEY_E])
    {
        pullUpRope();
    }

    if(ropeHooked())
        m_speed/=2;

    double maxspeed=0.1;


    if(!ropeHooked())
    {
        //speed limit
        if(m_velocity.X>maxspeed)
            m_velocity.X=maxspeed;
        else if(m_velocity.X<-maxspeed)
            m_velocity.X=-maxspeed;

        if(m_velocity.Y>maxspeed)
            m_velocity.Y=maxspeed;
        else if(m_velocity.Y<-maxspeed)
            m_velocity.Y=-maxspeed;
    }


    //friction
    m_velocity.X/=1.1;
    m_velocity.Y/=1.1;
}





