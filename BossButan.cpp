#include "BossButan.h"
#include "Map.h"
#include "Fireball.h"


BossButan::BossButan()
{
    m_name="bossbutan";
    m_active=false;
}






void BossButan::ini()
{
    Boss::ini();

    m_texture=GTexture::getInstance()->addGetTexture("../data/textures/bossbutan.png");

    m_life=10;
    cd_fireball.reset();


    BossPattern patrol=BossPattern();
    patrol.name="patrol";
    patrol.duration=3000;

    m_patterns.push_back(patrol);
}


void BossButan::update(double functionTime)
{
    if(m_active)
    {
        Boss::update(functionTime);

        //collision with rope: death
        if(collidedWithType("rope"))
        {
            m_life=0;
        }

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
        }

        //patterns
        if(m_current_pattern!=NULL)
        {
            if(m_current_pattern->name=="patrol")
            {
                //move
                moveToDir();
            }

            m_current_pattern->time_since_start.couler();
            if(m_current_pattern->time_since_start.ecouler(m_current_pattern->duration))
            {
                m_current_pattern=&m_patterns[0];
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
        }
    }
}




void BossButan::draw()
{
    if(m_active && m_visible)
    {
        glDisable(GL_LIGHTING);

        const Vector3D m_taille=m_size;

        glColor4ub(255,255,255,255);

        if(m_texture!=NULL)
            m_texture->bind();


        glPushMatrix();
        glTranslated(m_position.X,m_position.Y,m_position.Z);


        glBegin(GL_QUADS);

        glNormal3d(0.0,1.0,0.0);
        glTexCoord2d(1,0);               glVertex3d(m_taille.X,m_taille.Y,m_taille.Z*2);
        glTexCoord2d(1,1);    glVertex3d(m_taille.X,m_taille.Y,0);
        glTexCoord2d(0,1);               glVertex3d(-m_taille.X,m_taille.Y,0);
        glTexCoord2d(0,0);                          glVertex3d(-m_taille.X,m_taille.Y,m_taille.Z*2);

        glNormal3d(1.0,0.0,0.0);
        glTexCoord2d(1,0);               glVertex3d(m_taille.X,-m_taille.Y,m_taille.Z*2);
        glTexCoord2d(1,1);    glVertex3d(m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(0,1);               glVertex3d(m_taille.X,m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(0,0);                          glVertex3d(m_taille.X,m_taille.Y,m_taille.Z*2);

        glNormal3d(0.0,-1.0,0.0);
        glTexCoord2d(0,1);               glVertex3d(-m_taille.X,-m_taille.Y,m_taille.Z*2);
        glTexCoord2d(0,0);                          glVertex3d(-m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(1,0);               glVertex3d(m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(1,1);    glVertex3d(m_taille.X,-m_taille.Y,m_taille.Z*2);

        glNormal3d(-1.0,0.0,0.0);
        glTexCoord2d(0,1);               glVertex3d(-m_taille.X,m_taille.Y,m_taille.Z*2);
        glTexCoord2d(0,0);                          glVertex3d(-m_taille.X,m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(1,0);               glVertex3d(-m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(1,1);    glVertex3d(-m_taille.X,-m_taille.Y,m_taille.Z*2);

        glNormal3d(0.0,0.0,1.0);
        glTexCoord2d(0,1);               glVertex3d(m_taille.X,m_taille.Y,m_taille.Z*2);
        glTexCoord2d(0,0);                          glVertex3d(-m_taille.X,m_taille.Y,m_taille.Z*2);
        glTexCoord2d(1,0);               glVertex3d(-m_taille.X,-m_taille.Y,m_taille.Z*2);
        glTexCoord2d(1,1);    glVertex3d(m_taille.X,-m_taille.Y,m_taille.Z*2);

        glNormal3d(0.0,0.0,-1.0);
        glTexCoord2d(0,1);               glVertex3d(m_taille.X,m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(1,1);    glVertex3d(m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(1,0);               glVertex3d(-m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(0,0);                          glVertex3d(-m_taille.X,m_taille.Y,-m_taille.Z*0);

        glEnd();

        glPopMatrix();
    }
}




