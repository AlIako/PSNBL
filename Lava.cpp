#include "Lava.h"



Lava::Lava()
{
    m_texture=NULL;
    m_transparency=true;
    m_block=false;
    mosaic=7;
    m_speed=0;
    txtcord=Vector3D(0,0,0);
}

void Lava::ini()
{
    m_type="lava";
    if(gtext!=NULL)
    {
        gtext->addTexture("../data/textures/lava.png");
        m_texture=gtext->getTexture("../data/textures/lava.png");
    }

    dampvalue.setParameter(15, 2);
    dampvalue = 2;
    Object::ini();
}


void Lava::update(double functionTime)
{
    m_size.Z+=m_speed*functionTime/10;

    //text value damping
    dampvalue.update(functionTime/10.0);
    txtcord.X += dampvalue/5;
    txtcord.Y += dampvalue/5;

    if(dampvalue>=1)
        dampvalue = -2;
    if(dampvalue<=-1)
        dampvalue = 2;
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
    glTexCoord2d(m_taille.X*2/mosaic-txtcord.Y/100,0-txtcord.X/100);               glVertex3d(m_taille.X,m_taille.Y,m_taille.Z*2);
    glTexCoord2d(m_taille.X*2/mosaic-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);    glVertex3d(m_taille.X,m_taille.Y,0);
    glTexCoord2d(0-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);               glVertex3d(-m_taille.X,m_taille.Y,0);
    glTexCoord2d(0-txtcord.Y/100,0-txtcord.X/100);                          glVertex3d(-m_taille.X,m_taille.Y,m_taille.Z*2);

    glNormal3d(1.0,0.0,0.0);
    glTexCoord2d(m_taille.Y*2/mosaic+txtcord.Y/100,0+txtcord.X/100);               glVertex3d(m_taille.X,-m_taille.Y,m_taille.Z*2);
    glTexCoord2d(m_taille.Y*2/mosaic+txtcord.Y/100,m_taille.Z*2/mosaic+txtcord.X/100);    glVertex3d(m_taille.X,-m_taille.Y,0);
    glTexCoord2d(0+txtcord.Y/100,m_taille.Z*2/mosaic+txtcord.X/100);               glVertex3d(m_taille.X,m_taille.Y,0);
    glTexCoord2d(0+txtcord.Y/100,0+txtcord.X/100);                          glVertex3d(m_taille.X,m_taille.Y,m_taille.Z*2);

    glNormal3d(0.0,-1.0,0.0);
    glTexCoord2d(0-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);               glVertex3d(-m_taille.X,-m_taille.Y,m_taille.Z*2);
    glTexCoord2d(0-txtcord.Y/100,0-txtcord.X/100);                          glVertex3d(-m_taille.X,-m_taille.Y,0);
    glTexCoord2d(m_taille.X*2/mosaic-txtcord.Y/100,0-txtcord.X/100);               glVertex3d(m_taille.X,-m_taille.Y,0);
    glTexCoord2d(m_taille.X*2/mosaic-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);    glVertex3d(m_taille.X,-m_taille.Y,m_taille.Z*2);

    glNormal3d(-1.0,0.0,0.0);
    glTexCoord2d(0-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);               glVertex3d(-m_taille.X,m_taille.Y,m_taille.Z*2);
    glTexCoord2d(0-txtcord.Y/100,0-txtcord.X/100);                          glVertex3d(-m_taille.X,m_taille.Y,0);
    glTexCoord2d(m_taille.Y*2/mosaic-txtcord.Y/100,0-txtcord.X/100);               glVertex3d(-m_taille.X,-m_taille.Y,0);
    glTexCoord2d(m_taille.Y*2/mosaic-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);    glVertex3d(-m_taille.X,-m_taille.Y,m_taille.Z*2);

    glNormal3d(0.0,0.0,1.0);
    glTexCoord2d(0+txtcord.X/100,m_taille.X*2/mosaic+txtcord.Y/100);               glVertex3d(m_taille.X,m_taille.Y,m_taille.Z*2);
    glTexCoord2d(0+txtcord.X/100,0+txtcord.Y/100);                          glVertex3d(-m_taille.X,m_taille.Y,m_taille.Z*2);
    glTexCoord2d(m_taille.Y*2/mosaic+txtcord.X/100,0+txtcord.Y/100);               glVertex3d(-m_taille.X,-m_taille.Y,m_taille.Z*2);
    glTexCoord2d(m_taille.Y*2/mosaic+txtcord.X/100,m_taille.X*2/mosaic+txtcord.Y/100);    glVertex3d(m_taille.X,-m_taille.Y,m_taille.Z*2);

    glNormal3d(0.0,0.0,-1.0);
    glTexCoord2d(0,m_taille.X*2/mosaic);               glVertex3d(m_taille.X,m_taille.Y,0);
    glTexCoord2d(0,0);                          glVertex3d(-m_taille.X,m_taille.Y,0);
    glTexCoord2d(m_taille.Y*2/mosaic,0);               glVertex3d(-m_taille.X,-m_taille.Y,0);
    glTexCoord2d(m_taille.Y*2/mosaic,m_taille.X*2/mosaic);    glVertex3d(m_taille.X,-m_taille.Y,0);

    glEnd();

    glPopMatrix();

    glDisable(GL_BLEND);
}



