#include "Damage.h"

Damage::Damage()
{
    m_block=false;
    m_gravity=false;
    //m_physical=false;

    m_damageValue=1;
    m_damageType=3;//burst

    m_type="damage";

    m_visible=false;
}


void Damage::ini()
{
    Object::ini();
    m_texture=GTexture::getInstance()->addGetTexture("../data/textures/black.jpg");
}


void Damage::update(double functionTime)
{
    ft=functionTime;

    time_since_ini.couler();
    if(time_since_ini.ecouler(100))
    {
        m_life=0;
    }
    else
    {
        //damage everything
        for(unsigned int i=0;i<m_colliding.size();i++)
        {
            action(0,m_colliding[i]);//damage
        }
    }
}

void Damage::action(int type, Object* o)
{
    if(type==0 && o!=NULL)//damage
    {
        if(o->getType()=="player")
        {
            o->loseLife(m_damageValue);//kill bonus
            o->setDeathCause(m_damageType);
        }
    }
}


void Damage::draw()
{
    if(m_visible)
    {
        Lighting::getInstance()->glDisableLighting();

        int mosaic=1;
        const Vector3D m_taille=m_size;

        glColor4ub(255,255,255,255);

        if(m_texture!=NULL)
            m_texture->bind();


        glPushMatrix();
        glTranslated(m_position.X,m_position.Y,m_position.Z);
        //glRotated(m_rotation.Z,0,0,1);

        glBegin(GL_QUADS);

        glNormal3d(0.0,1.0,0.0);
        glTexCoord2d(m_taille.X*2/mosaic,0);               glVertex3d(m_taille.X,m_taille.Y,m_taille.Z*2);
        glTexCoord2d(m_taille.X*2/mosaic,m_taille.Z*2/mosaic);    glVertex3d(m_taille.X,m_taille.Y,0);
        glTexCoord2d(0,m_taille.Z*2/mosaic);               glVertex3d(-m_taille.X,m_taille.Y,0);
        glTexCoord2d(0,0);                          glVertex3d(-m_taille.X,m_taille.Y,m_taille.Z*2);

        glNormal3d(1.0,0.0,0.0);
        glTexCoord2d(m_taille.Y*2/mosaic,0);               glVertex3d(m_taille.X,-m_taille.Y,m_taille.Z*2);
        glTexCoord2d(m_taille.Y*2/mosaic,m_taille.Z*2/mosaic);    glVertex3d(m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(0,m_taille.Z*2/mosaic);               glVertex3d(m_taille.X,m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(0,0);                          glVertex3d(m_taille.X,m_taille.Y,m_taille.Z*2);

        glNormal3d(0.0,-1.0,0.0);
        glTexCoord2d(0,m_taille.Z*2/mosaic);               glVertex3d(-m_taille.X,-m_taille.Y,m_taille.Z*2);
        glTexCoord2d(0,0);                          glVertex3d(-m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(m_taille.X*2/mosaic,0);               glVertex3d(m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(m_taille.X*2/mosaic,m_taille.Z*2/mosaic);    glVertex3d(m_taille.X,-m_taille.Y,m_taille.Z*2);

        glNormal3d(-1.0,0.0,0.0);
        glTexCoord2d(0,m_taille.Z*2/mosaic);               glVertex3d(-m_taille.X,m_taille.Y,m_taille.Z*2);
        glTexCoord2d(0,0);                          glVertex3d(-m_taille.X,m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(m_taille.Y*2/mosaic,0);               glVertex3d(-m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(m_taille.Y*2/mosaic,m_taille.Z*2/mosaic);    glVertex3d(-m_taille.X,-m_taille.Y,m_taille.Z*2);

        glNormal3d(0.0,0.0,1.0);
        glTexCoord2d(0,m_taille.X*2/mosaic);               glVertex3d(m_taille.X,m_taille.Y,m_taille.Z*2);
        glTexCoord2d(0,0);                          glVertex3d(-m_taille.X,m_taille.Y,m_taille.Z*2);
        glTexCoord2d(m_taille.Y*2/mosaic,0);               glVertex3d(-m_taille.X,-m_taille.Y,m_taille.Z*2);
        glTexCoord2d(m_taille.Y*2/mosaic,m_taille.X*2/mosaic);    glVertex3d(m_taille.X,-m_taille.Y,m_taille.Z*2);

        glNormal3d(0.0,0.0,-1.0);
        glTexCoord2d(0,m_taille.X*2/mosaic);               glVertex3d(m_taille.X,m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(m_taille.Y*2/mosaic,m_taille.X*2/mosaic);    glVertex3d(m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(m_taille.Y*2/mosaic,0);               glVertex3d(-m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(0,0);                          glVertex3d(-m_taille.X,m_taille.Y,-m_taille.Z*0);

        glEnd();




        glPopMatrix();

        glColor3ub(255,255,255);

    }
}
