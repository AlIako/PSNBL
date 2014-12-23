#include "Rope.h"





Rope::Rope()
{
    m_block=true;

    m_hooked=false;
    m_physical=true;

    m_type="rope";
}


void Rope::update(double functionTime)
{
    ft=functionTime;
    if(!m_hooked)
    {
        if(m_collided)
        {
            m_hooked=true;
            m_velocity=Vector3D(0,0,0);
            m_physical=false;
            m_block=false;
            m_end=m_position;
        }
    }
    else
    {

    }
}


void Rope::ini()
{
    m_type="rope";
    if(gtext!=NULL)
    {
        gtext->addTexture("../data/textures/rope.jpg");
        m_texture=gtext->getTexture("../data/textures/rope.jpg");
    }

    m_size=Vector3D(0.25,0.25,0.25);
}


void Rope::ini(Vector3D start, Vector3D dir)
{
    ini();

    m_position=start;
    m_start=start;
    m_direction=dir;


    m_velocity=m_direction;

}

void Rope::draw()
{
    const Vector3D m_taille=m_size;
    const double mosaic=2;

    glColor3ub(255,255,255);

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
}



