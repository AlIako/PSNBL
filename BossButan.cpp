#include "BossButan.h"




BossButan::BossButan()
{
    m_name="bossbutan";
}






void BossButan::ini()
{
    Boss::ini();

    GTexture::getInstance()->addTexture("../data/textures/chardead.png");
    m_texture=GTexture::getInstance()->getTexture("../data/textures/chardead.png");

    m_life=10;


    BossPattern patrol=BossPattern();
    patrol.name="patrol";
    patrol.duration=3000;

    m_patterns.push_back(patrol);

    m_current_pattern=&m_patterns[0];
    iniPattern(m_current_pattern);
}


void BossButan::update(double functionTime)
{
    Boss::update(functionTime);

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



void BossButan::iniPattern(BossPattern* pat)
{
    if(pat!=NULL)
    {
        pat->time_since_start.reset();
        if(pat->name=="patrol")
        {
            double movementRange=20;

            //find next destination
            m_destination=m_position+Vector3D(myDoubleRand(-movementRange,movementRange),myDoubleRand(-movementRange,movementRange),myDoubleRand(-movementRange,movementRange));

            //set vector direction
            m_direction=(m_destination-m_position).normalize();
        }
    }
}




void BossButan::draw()
{
    if(m_visible)
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




