#include "Player.h"
#define MAPSIZE 50




Player::Player()
{
    m_texture=NULL;
    m_startpos=Vector3D(2,-45,30);
    m_position=m_startpos;

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
    m_gasing=false;

    m_maxspeed=0.1;

    m_deathCause=0;
}

void Player::update(double functionTime)
{
    if(m_collided)
    {
        m_jumping=false;
        //m_collided=false;

        //grabbed a bonus?
        for(unsigned int i=0;i<m_colliding.size();i++)
        {
            if(m_colliding[i]->getType()=="bonus")
            {
                m_colliding[i]->loseLife(m_colliding[i]->getLife());
                if(Online::getInstance()!=NULL)
                {
                    infosSocket s;
                    s.confirmationID=-1;
                    s.type=10;
                    s.variable[1]=m_colliding[i]->getPos().X;
                    s.variable[2]=m_colliding[i]->getPos().Y;
                    s.variable[3]=m_colliding[i]->getPos().Z;

                    Online::getInstance()->sendSocket(s);
                }
            }
            else if(m_colliding[i]->getType()=="lava")
            {
                m_deathCause=1;
            }
        }
    }

    if(hookedToRope())
    {
        if(m_rope->getLife()<=0)
            unlinkRope();

        if(ropeHooked())
        {
            //m_jumping=false;
            if(m_onTopOf==NULL)
                m_rope->pullMe(this);
        }
    }

    Object::update(functionTime);

    if(m_onTopOf!=NULL)
        m_jumping=false;
}
void Player::jump()
{
    if(m_life>0)
    {
        if(m_onTopOf!=NULL && !m_jumping && (fabs(m_velocity.Z)<0.1 || ropeHooked()))
        {
            m_jumping=true;

            if(m_velocity.Z<0.4)
                setVel(Vector3D(getVel().X,getVel().Y,0.4));


            //re set rope distance to actual distance
            if(m_rope!=NULL)
            {
                m_rope->setNowDistance();
            }
            //unlinkRope();
        }
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
    if(GTexture::getInstance())
    {
        GTexture::getInstance()->addTexture("../data/textures/char1.png");
        m_texture=GTexture::getInstance()->getTexture("../data/textures/char1.png");

        GTexture::getInstance()->addTexture("../data/textures/chardead.png");
        m_textureDead=GTexture::getInstance()->getTexture("../data/textures/chardead.png");
    }

    //spells
    addSpell(new SpellRope());
    addSpell(new SpellJump());
    addSpell(new SpellLongJump());
    addSpell(new SpellPullUp());
    //addSpell(new SpellRopeBoost());
}

void Player::draw()
{
    glColor3ub(255,255,255);



    glPushMatrix();
    glTranslated(m_position.X,m_position.Y,m_position.Z+1);
    glRotated(m_rotation.Z,0,0,1);
    if(m_life>0)
    {
        if(m_texture!=NULL)
            m_texture->bind();
    }
    else
    {
        if(m_textureDead!=NULL)
            m_textureDead->bind();
    }

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
    //cerr<<"press "<< k <<" key"<<endl;
}

void Player::resurrect()
{
    Object::resurrect();
    m_position=m_startpos;
    m_life=100;

    unlinkRope();
}


void Player::move()
{
    if(m_life<=0)
    {
        m_pressed[UP]=false;
        m_pressed[DOWN]=false;
        m_pressed[LEFT]=false;
        m_pressed[RIGHT]=false;
        m_pressed[KEY_E]=false;
    }

    //hook
    if(m_pressed[KEY_E] && getSpell("pullup")!=NULL)
        pullUpRope();

    //movement on ground
    if(m_onTopOf!=NULL)
    {
        moveXY(&m_movementVelocity);
        //friction on ground
        m_movementVelocity.X/=1.1;
        m_movementVelocity.Y/=1.1;
        m_velocity.X/=1.1;
        m_velocity.Y/=1.1;
    }
    else//movement in the air
    {
        if(ropeHooked())
        {
            if(m_gasing && getSpell("ropeboost")!=NULL)
            {
                moveXY(&m_velocity);

                const double spd=1.03;
                m_velocity.X/=spd;
                m_velocity.Y/=spd;
            }
            else
            {
                /*moveXY(&m_movementVelocity);
                m_movementVelocity.X/=1.1;
                m_movementVelocity.Y/=1.1;*/
                moveXY(&m_velocity);

                const double spd=1.03;
                m_velocity.X/=spd;
                m_velocity.Y/=spd;
            }
        }
        else
        {
            moveXY(&m_movementVelocity);
            m_movementVelocity.X/=1.1;
            m_movementVelocity.Y/=1.1;
        }
    }
}

void Player::moveXY(Vector3D* vel)
{
    //Vector3D m_saveVel=m_movementVelocity;

    if(m_pressed[UP])
    {
        vel->X+=m_speed*m_direction.X*ft;
        vel->Y+=m_speed*m_direction.Y*ft;
        //m_position.Z+=m_speed*m_direction.Z;
    }
    if(m_pressed[DOWN])
    {
        vel->X-=m_speed*m_direction.X*ft;
        vel->Y-=m_speed*m_direction.Y*ft;
        //m_position.Z-=m_speed*m_direction.Z;
    }
    if(m_pressed[RIGHT])
    {
        vel->X+=m_direction.Y*m_speed*ft;
        vel->Y-=m_direction.X*m_speed*ft;
    }
    if(m_pressed[LEFT])
    {
        vel->X-=m_direction.Y*m_speed*ft;
        vel->Y+=m_direction.X*m_speed*ft;

    }

    /*double newLength=Vector3D(m_movementVelocity.X,m_movementVelocity.Y,0).length();
    double oldLength=Vector3D(m_saveVel.X,m_saveVel.Y,0).length();
    if(newLength>m_maxspeed && newLength>oldLength)//if we're too fast and new velocity greater than old
    {
        m_movementVelocity=m_saveVel;
    }*/
}

void Player::addSpell(Spell* s)
{
    if(s!=NULL)
    {
        bool spellFound=false;
        for(unsigned int i=0;i<m_spells.size();i++)
        {
            if(m_spells[i]->getName()==s->getName())
            {
                m_spells[i]=s;
                spellFound=true;
            }
        }

        if(!spellFound)
        {
            m_spells.push_back(s);
        }
    }
}
Spell* Player::getSpell(string s)
{
    for(unsigned int i=0;i<m_spells.size();i++)
    {
        if(m_spells[i]->getName()==s)
            return m_spells[i];
    }
    return NULL;
}



