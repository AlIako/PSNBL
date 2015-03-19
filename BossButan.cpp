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

        //collision with rope: death
        if(collidedWithType("rope"))
        {
            m_life=0;
        }


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
                    cd_fireball.reset();
                    //find direction to player
                    vector<Player*>* p=Map::getInstance()->playerList;
                    Vector3D dir=((*p)[0]->getPos()-m_position).normalize();

                    //create fireball
                    vector<Object*>* o=Map::getInstance()->getObjects();
                    unsigned int ind=o->size();
                    o->push_back(new Fireball());
                    (*o)[ind]->setPos(m_position+dir*5);
                    (*o)[ind]->setDir(dir);
                    (*o)[ind]->ini();
                    (*o)[ind]->setSpeed(.5);
                }
            }
            else if(m_current_pattern->name=="rush")
            {
                //move

                //find direction to player
                vector<Player*>* p=Map::getInstance()->playerList;
                m_direction=((*p)[0]->getPos()-m_position).normalize();
                double dist=((*p)[0]->getPos()-m_position).length();

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
                int nextPatternID=myIntRand(0,m_patterns.size()-1);
                m_current_pattern=&m_patterns[nextPatternID];
                iniPattern(m_current_pattern);
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

            //set vector direction
            m_direction=(m_destination-m_position).normalize();

            rotaZDir();
        }
        else if(pat->name=="nova")
        {
            m_velocity=Vector3D(0,0,0);
            m_direction=m_velocity;
        }
    }
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




