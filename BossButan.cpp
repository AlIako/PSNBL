#include "BossButan.h"
#include "Map.h"
#include "Fireball.h"


BossButan::BossButan()
{
    m_name="bossbutan";
    m_active=false;
    m_speed=.1;
}






void BossButan::ini()
{
    Boss::ini();

    m_texture=GTexture::getInstance()->addGetTexture("../data/textures/bedrock.png");
    m_texture_fire=GTexture::getInstance()->addGetTexture("../data/textures/fire.jpg");

    m_life=100;
    cd_fireball.reset();


    BossPattern patrol=BossPattern();
    patrol.name="patrol";
    patrol.duration=3000;

    m_patterns.push_back(patrol);

    BossPattern nova=BossPattern();
    nova.name="nova";
    nova.duration=5000;

    m_patterns.push_back(nova);

    BossPattern rush=BossPattern();
    rush.name="rush";
    rush.duration=5000;

    m_patterns.push_back(rush);
}


void BossButan::update(double functionTime)
{
    if(m_active)
    {
        Boss::update(functionTime);

        m_life-=ft/100.0;

        m_rotation.X+=ft/8.0;
        m_rotation.Y+=ft/8.0;

        //patterns
        if(m_current_pattern!=NULL)
        {
            if(m_current_pattern->name=="patrol")
            {
                m_speed=.1;
                //move
                moveToDir();

                //fireball
                cd_fireball.couler();
                if(cd_fireball.ecouler(1000))
                {
                    if(Online::getInstance()->inControl())
                    {
                        cd_fireball.reset();
                        //find direction to player
                        Vector3D dir=(nearPlayer->getPos()-m_position).normalize();

                        action(3,dir);

                        //send socket
                        infosSocket s;
                        //s.confirmationID=Online::getInstance()->nextConfirmationID();
                        s.confirmationID=-1;
                        s.type=103;
                        s.variable[0]=0;
                        s.variable[1]=dir.X;
                        s.variable[2]=dir.Y;
                        s.variable[3]=dir.Z;
                        Online::getInstance()->sendSocket(s);
                    }
                }
            }
            else if(m_current_pattern->name=="rush" && target!=NULL)
            {
                //move

                //find direction to player
                m_direction=(target->getPos()-m_position).normalize();
                double dist=(target->getPos()-m_position).length();

                rotaZDir();

                if(dist>20)
                {
                    m_speed=1;
                    moveToDir();
                }
                else if(dist>10)
                {
                    m_speed=.1;
                    moveToDir();
                }
                else
                {
                    m_speed=0;
                    m_velocity=Vector3D(0,0,0);
                }
            }
            else if(m_current_pattern->name=="nova")
            {
                //fireball
                cd_fireball.couler();
                if(cd_fireball.ecouler(200))
                {
                    cd_fireball.reset();
                    for(int i=0;i<5;i++)
                    {
                        //set random direction
                        Vector3D dir=(Vector3D(myDoubleRand(-1,1),myDoubleRand(-1,1),myDoubleRand(-1,1))).normalize();

                        //create fireball
                        vector<Object*>* o=Map::getInstance()->getObjects();
                        unsigned int ind=o->size();
                        o->push_back(new Fireball());
                        (*o)[ind]->setPos(m_position+dir*10);
                        (*o)[ind]->setDir(dir);
                        (*o)[ind]->ini();
                        (*o)[ind]->setSpeed(.5);
                    }
                }
            }

            m_current_pattern->time_since_start.couler();
            if(m_current_pattern->time_since_start.ecouler(m_current_pattern->duration))
            {
                if(Online::getInstance()->inControl())
                {
                    int nextPatternID=myIntRand(0,m_patterns.size()-1);
                    m_current_pattern=&m_patterns[nextPatternID];
                    iniPattern(m_current_pattern);
                }
            }
        }

    }
}



void BossButan::iniPattern(BossPattern* pat)
{
    if(pat!=NULL)
    {
        pat->time_since_start.reset();
        if(pat->name=="patrol")
        {
            double movementRange=20;
            double movementRangeZ=5;

            //find next destination
            m_destination=m_startPosition+Vector3D(myDoubleRand(-movementRange,movementRange),
                                              myDoubleRand(-movementRange,movementRange),
                                              myDoubleRand(-movementRangeZ,movementRangeZ));

            action(1,m_destination);

            //send socket
            infosSocket s;
            s.confirmationID=Online::getInstance()->nextConfirmationID();
            s.type=101;
            s.variable[0]=0;
            s.variable[1]=m_destination.X;
            s.variable[2]=m_destination.Y;
            s.variable[3]=m_destination.Z;
            Online::getInstance()->sendSocket(s);
        }
        else if(pat->name=="rush")
        {
            target=randomPlayer();
            action(4,Vector3D(0,0,0));

            //send socket
            infosSocket s;
            s.confirmationID=Online::getInstance()->nextConfirmationID();
            s.type=104;
            s.variable[0]=0;
            s.variable[1]=target->getPos().X;
            s.variable[2]=target->getPos().Y;
            s.variable[3]=target->getPos().Z;
            Online::getInstance()->sendSocket(s);
        }
        else if(pat->name=="nova")
        {
            action(2,Vector3D(0,0,0));

            //send socket
            infosSocket s;
            s.confirmationID=Online::getInstance()->nextConfirmationID();
            s.type=102;
            s.variable[0]=0;
            Online::getInstance()->sendSocket(s);
        }
    }
}

void BossButan::action(int type, Vector3D v)
{
    if(type==1)
    {
        Tracer::getInstance()->trace("boss","pattern patrol");
        setPattern("patrol");

        //set vector direction
        m_direction=(v-m_position).normalize();

        rotaZDir();
    }
    else if(type==2)
    {
        Tracer::getInstance()->trace("boss","pattern nova");
        setPattern("nova");

        m_velocity=Vector3D(0,0,0);
        m_direction=m_velocity;
    }
    else if(type==3)
    {
        Tracer::getInstance()->trace("boss","fireball");
        //create fireball
        vector<Object*>* o=Map::getInstance()->getObjects();
        unsigned int ind=o->size();
        o->push_back(new Fireball());
        (*o)[ind]->setPos(m_position+v*5);
        (*o)[ind]->setDir(v);
        (*o)[ind]->ini();
        (*o)[ind]->setSpeed(.5);
    }
    else if(type==4)
    {
        Tracer::getInstance()->trace("boss","pattern rush");
        setPattern("rush");
        target=nearestPlayerFrom(v);
    }
}

void BossButan::action(int type, Object* o)
{
    Boss::action(type,o);
}



void BossButan::draw()
{
    if(m_active && m_visible)
    {
        Lighting::getInstance()->glDisableLighting();
        if(m_texture!=NULL)
            m_texture->bind();

        glPushMatrix();
        glTranslated(m_position.X,m_position.Y,m_position.Z+m_size.X/2);
        glRotated(m_rotation.Z,0,0,1);

        GLUquadric* params = gluNewQuadric();
        gluQuadricTexture(params,GL_TRUE);

        //face
        double bs=1;
        double ds=3.5;
        glTranslated(ds,0,0);

        glTranslated(0,bs,0);
        glTranslated(0,bs,bs);
        gluSphere(params,m_size.X/2,5,5);

        glTranslated(0,-bs*3,-bs);
        glTranslated(0,-bs,bs);
        gluSphere(params,m_size.X/2,5,5);
        glTranslated(0,bs*2,-bs);


        glTranslated(0,0,-3);

        glTranslated(0,bs,0);
        gluSphere(params,m_size.X/2,5,5);
        glTranslated(0,bs,bs);
        gluSphere(params,m_size.X/2,5,5);

        glTranslated(0,-bs*3,-bs);
        gluSphere(params,m_size.X/2,5,5);
        glTranslated(0,-bs,bs);
        gluSphere(params,m_size.X/2,5,5);
        glTranslated(0,bs*2,-bs);

        glTranslated(0,0,3);

        glTranslated(-ds,0,0);

        //body
        glRotated(m_rotation.X,1,0,0);
        glRotated(m_rotation.Y,0,1,0);
        gluSphere(params,m_size.X+m_size.X/2,5,5);


        //fire
        if(m_texture_fire!=NULL)
            m_texture_fire->bind();

        glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        glEnable(GL_BLEND);

        glRotated(-2*m_rotation.X,1,0,0);
        glRotated(-2*m_rotation.Y,0,1,0);
        glRotated(-2*m_rotation.Z,0,0,1);
        gluSphere(params,m_size.X+m_size.X,5,5);

        gluDeleteQuadric(params);

        glPopMatrix();

        glDisable(GL_BLEND);
        Lighting::getInstance()->glEnableLighting();
    }
}




