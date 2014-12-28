#include "Lava.h"



Lava::Lava()
{
    m_texture=NULL;
    m_transparency=true;
    m_block=false;
    mosaic=5;
    m_speed=0;
    txtcord=Vector3D(0,0,0);
    txtdir=true;
}

void Lava::ini()
{
    m_type="lava";
    if(gtext!=NULL)
    {
        gtext->addTexture("../data/textures/lava.png");
        m_texture=gtext->getTexture("../data/textures/lava.png");
    }

    Object::ini();
}


void Lava::update(double functionTime)
{
    m_size.Z+=m_speed*functionTime/10;

    //text coord
    /*txtcord+=dirmov*functionTime;
    if(txtdir)
        dirmov.Y+=functionTime;
    else
        dirmov.Y-=functionTime;
    if(txtcord.Y>0.1)
    {
        dirmov.Y-=functionTime;
    }
    if(txtcord.Y<0.1)
    {
        dirmov.Y+=functionTime;
    }*/
}


void Lava::draw()
{
    const Vector3D m_taille=m_size;

    glColor3ub(255,255,255);

    if(m_texture!=NULL)
        m_texture->bind();


    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    //glEnable(GL_BLEND);
    glPushMatrix();
    glTranslated(m_position.X,m_position.Y,m_position.Z);

    glBegin(GL_QUADS);

    glNormal3d(0.0,1.0,0.0);
    glTexCoord2d(m_taille.X*2/mosaic-txtcord.Y/100,0-txtcord.X/100);               glVertex3d(m_taille.X,m_taille.Y,m_taille.Z);
    glTexCoord2d(m_taille.X*2/mosaic-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);    glVertex3d(m_taille.X,m_taille.Y,-m_taille.Z);
    glTexCoord2d(0-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);               glVertex3d(-m_taille.X,m_taille.Y,-m_taille.Z);
    glTexCoord2d(0-txtcord.Y/100,0-txtcord.X/100);                          glVertex3d(-m_taille.X,m_taille.Y,m_taille.Z);

    glNormal3d(1.0,0.0,0.0);
    glTexCoord2d(m_taille.Y*2/mosaic+txtcord.Y/100,0+txtcord.X/100);               glVertex3d(m_taille.X,-m_taille.Y,m_taille.Z);
    glTexCoord2d(m_taille.Y*2/mosaic+txtcord.Y/100,m_taille.Z*2/mosaic+txtcord.X/100);    glVertex3d(m_taille.X,-m_taille.Y,-m_taille.Z);
    glTexCoord2d(0+txtcord.Y/100,m_taille.Z*2/mosaic+txtcord.X/100);               glVertex3d(m_taille.X,m_taille.Y,-m_taille.Z);
    glTexCoord2d(0+txtcord.Y/100,0+txtcord.X/100);                          glVertex3d(m_taille.X,m_taille.Y,m_taille.Z);

    glNormal3d(0.0,-1.0,0.0);
    glTexCoord2d(0-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);               glVertex3d(-m_taille.X,-m_taille.Y,m_taille.Z);
    glTexCoord2d(0-txtcord.Y/100,0-txtcord.X/100);                          glVertex3d(-m_taille.X,-m_taille.Y,-m_taille.Z);
    glTexCoord2d(m_taille.X*2/mosaic-txtcord.Y/100,0-txtcord.X/100);               glVertex3d(m_taille.X,-m_taille.Y,-m_taille.Z);
    glTexCoord2d(m_taille.X*2/mosaic-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);    glVertex3d(m_taille.X,-m_taille.Y,m_taille.Z);

    glNormal3d(-1.0,0.0,0.0);
    glTexCoord2d(0-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);               glVertex3d(-m_taille.X,m_taille.Y,m_taille.Z);
    glTexCoord2d(0-txtcord.Y/100,0-txtcord.X/100);                          glVertex3d(-m_taille.X,m_taille.Y,-m_taille.Z);
    glTexCoord2d(m_taille.Y*2/mosaic-txtcord.Y/100,0-txtcord.X/100);               glVertex3d(-m_taille.X,-m_taille.Y,-m_taille.Z);
    glTexCoord2d(m_taille.Y*2/mosaic-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);    glVertex3d(-m_taille.X,-m_taille.Y,m_taille.Z);

    glNormal3d(0.0,0.0,1.0);
    glTexCoord2d(0+txtcord.X/100,m_taille.X*2/mosaic+txtcord.Y/100);               glVertex3d(m_taille.X,m_taille.Y,m_taille.Z);
    glTexCoord2d(0+txtcord.X/100,0+txtcord.Y/100);                          glVertex3d(-m_taille.X,m_taille.Y,m_taille.Z);
    glTexCoord2d(m_taille.Y*2/mosaic+txtcord.X/100,0+txtcord.Y/100);               glVertex3d(-m_taille.X,-m_taille.Y,m_taille.Z);
    glTexCoord2d(m_taille.Y*2/mosaic+txtcord.X/100,m_taille.X*2/mosaic+txtcord.Y/100);    glVertex3d(m_taille.X,-m_taille.Y,m_taille.Z);

    glNormal3d(0.0,0.0,-1.0);
    glTexCoord2d(0,m_taille.X*2/mosaic);               glVertex3d(m_taille.X,m_taille.Y,-m_taille.Z);
    glTexCoord2d(0,0);                          glVertex3d(-m_taille.X,m_taille.Y,-m_taille.Z);
    glTexCoord2d(m_taille.Y*2/mosaic,0);               glVertex3d(-m_taille.X,-m_taille.Y,-m_taille.Z);
    glTexCoord2d(m_taille.Y*2/mosaic,m_taille.X*2/mosaic);    glVertex3d(m_taille.X,-m_taille.Y,-m_taille.Z);

    glEnd();

    glPopMatrix();

    glDisable(GL_BLEND);
}



