#include "Player.h"
#include "Map.h"
#include "Fireball.h"
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

    testMode=false;
    //testMode=true;
}

void Player::update(double functionTime)
{
    if(m_collided)
    {
        //m_jumping=false;
        //m_collided=false;

        //grabbed a bonus?
        for(unsigned int i=0;i<m_colliding.size();i++)
        {
            if(m_colliding[i]->getType()=="bonus")
            {
                m_colliding[i]->loseLife(m_colliding[i]->getLife());//kill bonus
                if(m_colliding[i]->getName()!="rope" && m_colliding[i]->getName()!="longjump")
                {
                    if(Online::getInstance()->active())
                    {
                        infosSocket s;
                        s.confirmationID=Online::getInstance()->nextConfirmationID();
                        s.type=10;
                        s.variable[1]=m_colliding[i]->getPos().X;
                        s.variable[2]=m_colliding[i]->getPos().Y;
                        s.variable[3]=m_colliding[i]->getPos().Z;

                        Online::getInstance()->sendSocket(s);
                    }
                    if(m_colliding[i]->getName()=="health")
                    {
                        Gsounds::getInstance()->play("../data/sounds/health.wav");
                        loseLife(-10);
                        if(m_life>100)
                            m_life=100;
                    }
                }
                else if(m_colliding[i]->getName()=="rope")
                {
                    if(Online::getInstance()->active())
                    {
                        infosSocket s;
                        s.confirmationID=Online::getInstance()->nextConfirmationID();
                        s.type=16;
                        s.variable[1]=Spell::nameToId("rope");
                        Online::getInstance()->sendSocket(s);
                    }

                    if(0&&getSpell("rope")==NULL)
                        Interface::getInstance()->warning("../data/textures/interface/warning/gotrope.png",0.05,5000);
                    addSpell(new SpellRope());
                }
            }
            else if(m_colliding[i]->getType()=="projectile")
            {
                m_colliding[i]->action(0);//destroy projectile
            }
            else if(m_colliding[i]->getType()=="damage")
            {
                m_colliding[i]->action(0,this);//get damaged
            }
            else if(m_colliding[i]->getType()=="fogger" || m_colliding[i]->getType()=="fader" || m_colliding[i]->getType()=="warninger")
            {
                m_colliding[i]->action(0);
            }
            else if(m_colliding[i]->getType()=="lava")
            {
                m_deathCause=1;//burn

                //if deep enough, go back up
                if(m_velocity.Z<.05 && m_position.Z<m_colliding[i]->getPos().Z+m_colliding[i]->getSize().Z*2)
                    m_velocity.Z+=ft/75.0;
            }
            else if(m_colliding[i]->getType()=="block" && m_colliding[i]->getName()=="jumpBlock")
            {
                m_velocity.Z=.8;
                Tracer::getInstance()->trace("jumpblock","jumpblock");
            }
            else if(m_colliding[i]->getType()=="flux" && m_colliding[i]->getName()=="flux")
            {
                if(m_velocity.Z<.5)
                    m_velocity.Z+=.02;
                //Tracer::getInstance()->trace("jumpblock","jumpblock");
            }
            /*else if(m_colliding[i]->getType()=="rope")
            {
                //get pulled by a rope
                if(m_rope==NULL || m_rope!=m_colliding[i])
                {
                    m_colliding[i]->action(0,this);
                }
            }*/
        }
    }

    //get pulled by rope and stuff
    if(hookedToRope())
    {
        if(m_rope->getLife()<=0)
            unlinkRope();

        if(ropeHooked())
        {
            if(m_onTopOf==NULL)
                m_rope->pullMe(this);
        }
    }

    Object::update(functionTime);

    //on top of an object
    if(m_onTopOf!=NULL)
    {
        if(m_jumping)
            Tracer::getInstance()->trace("jump","rdy to jump again");
        m_jumping=false;
    }

}

void Player::updateMulti(double functionTime)
{
    for(unsigned int i=0;i<m_spells.size();i++)
        m_spells[i]->update(functionTime);

}


void Player::updateRope()
{
    if(m_rope!=NULL)
    {
        if(m_rope->isHooked())
            m_rope->setPos(m_position);
    }
}


bool Player::jump()
{
    if(m_life>0)
    {
        if((m_onTopOf!=NULL && !m_jumping)/* || ropeHooked()*/ || testMode)
        {
            m_jumping=true;

            if(m_velocity.Z<0.4)//dont jump to reduce velocity Z
                setVel(Vector3D(getVel().X,getVel().Y,0.4));


            //re set rope distance to actual distance
            if(m_rope!=NULL)
            {
                m_rope->setNowDistance();
            }
            //unlinkRope();

            Tracer::getInstance()->trace("player","jump");

            return true;
        }
    }
    return false;
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
    //m_jumping=false;

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

    GTexture::getInstance()->addTexture("../data/textures/spells/rope.png");
    //spells
    if(testMode)
        addSpell(new SpellRope());
    addSpell(new SpellJump());
    addSpell(new SpellLongJump());
    //addSpell(new SpellPullUp());
    //addSpell(new SpellRopeBoost());
}

void Player::draw()
{
    glColor3ub(255,255,255);

    Lighting::getInstance()->glDisableLighting();
    Lighting::getInstance()->glEnableLighting();

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

                m_velocity.X/=1.01;
                m_velocity.Y/=1.01;
            }
            else
            {
            m_speed/=4.0;

            moveXY(&m_velocity);
            m_velocity.X/=1.01;
            m_velocity.Y/=1.01;

            m_speed*=4.0;
            }
        }
        else
        {
            moveXY(&m_movementVelocity);
            m_movementVelocity.X/=1.1;
            m_movementVelocity.Y/=1.1;

            m_velocity.X/=1.01;
            m_velocity.Y/=1.01;
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

void Player::applyGravity()
{
    if(/* !ropeHooked() && */m_physical && m_gravity)
    {
        m_velocity.Z-=0.01*ft;
    }
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
                s->ini();
                m_spells[i]=s;
                spellFound=true;
            }
        }

        if(!spellFound)
        {
            s->ini();
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



