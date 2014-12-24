#include "Rope.h"





Rope::Rope()
{
    m_block=true;

    m_hooked=false;
    m_physical=true;

    m_type="rope";
    linkedTo=NULL;

    m_speed=0.05;
}


void Rope::update(double functionTime)
{
    ft=functionTime;
    if(!m_hooked)
    {
        m_end=m_position;
        if(m_collided)
        {
            cerr<<"update hook"<<endl;
            m_hooked=true;
            m_velocity=Vector3D(0,0,0);
            m_physical=false;
            m_block=false;
            m_end=m_position;
            m_distance=distance2V(m_start,m_end)-2;

            cerr<<"distance: "<<m_distance<<endl;
        }
    }
    else
    {
        if(linkedTo!=NULL)
        {
            //pull your player
            if ((m_end-linkedTo->getPos()).length() > m_distance )
                // we're past the end of our rope -> pull the avatar back in
                linkedTo->setVel(linkedTo->getVel()+(m_end-linkedTo->getPos()).normalize()*ft/40);
        }
        else//if player isnt attached to rope anymore
        {
            simulLinked.applyGravity();
            simulLinked.applyPhysics();

            if ((m_end-simulLinked.getPos()).length() > m_distance )
                simulLinked.setVel(simulLinked.getVel()+(m_end-simulLinked.getPos()).normalize()*ft/40);
        }
    }



    //update start pos
    if(linkedTo!=NULL)
        m_start=linkedTo->getPos();
    else//if player isnt attached to rope anymore
        m_start=simulLinked.getPos();
}

void Rope::pullUp()
{
    cerr<<"pull up rope: "<< m_distance << endl;
    m_distance-=100*ft;
}
void Rope::pullDown()
{

}


void Rope::unlink()
{
    if(linkedTo!=NULL)
        simulLinked=*linkedTo;

    linkedTo=NULL;
}

void Rope::ini()
{
    m_type="rope";
    if(gtext!=NULL)
    {
        gtext->addTexture("../data/textures/rope.jpg");
        m_texture=gtext->getTexture("../data/textures/rope.jpg");
    }

    m_size=Vector3D(0.05,0.05,0.05);
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

    glBegin(GL_QUADS);
    glNormal3d(0.0,1.0,0.0);
    glTexCoord2d(m_taille.X*2/mosaic,0);               glVertex3d(m_end.X+m_taille.X,m_end.Y+m_taille.Y,m_end.Z+m_taille.Z*2);
    glTexCoord2d(m_taille.X*2/mosaic,m_taille.Z*2/mosaic);    glVertex3d(m_start.X+m_taille.X,m_start.Y+m_taille.Y,m_start.Z-m_taille.Z*0);
    glTexCoord2d(0,m_taille.Z*2/mosaic);               glVertex3d(m_start.X-m_taille.X,m_start.Y+m_taille.Y,m_start.Z-m_taille.Z*0);
    glTexCoord2d(0,0);                          glVertex3d(m_end.X-m_taille.X,m_end.Y+m_taille.Y,m_end.Z+m_taille.Z*2);

    glNormal3d(1.0,0.0,0.0);
    glTexCoord2d(m_taille.Y*2/mosaic,0);               glVertex3d(m_end.X+m_taille.X,m_end.Y-m_taille.Y,m_end.Z+m_taille.Z*2);
    glTexCoord2d(m_taille.Y*2/mosaic,m_taille.Z*2/mosaic);    glVertex3d(m_start.X+m_taille.X,m_start.Y-m_taille.Y,m_start.Z-m_taille.Z*0);
    glTexCoord2d(0,m_taille.Z*2/mosaic);               glVertex3d(m_start.X+m_taille.X,m_start.Y+m_taille.Y,m_start.Z-m_taille.Z*0);
    glTexCoord2d(0,0);                          glVertex3d(m_end.X+m_taille.X,m_end.Y+m_taille.Y,m_end.Z+m_taille.Z*2);

    glNormal3d(0.0,-1.0,0.0);
    glTexCoord2d(0,m_taille.Z*2/mosaic);               glVertex3d(m_end.X-m_taille.X,m_end.Y-m_taille.Y,m_end.Z+m_taille.Z*2);
    glTexCoord2d(0,0);                          glVertex3d(m_start.X-m_taille.X,m_start.Y-m_taille.Y,m_start.Z-m_taille.Z*0);
    glTexCoord2d(m_taille.X*2/mosaic,0);               glVertex3d(m_start.X+m_taille.X,m_start.Y-m_taille.Y,m_start.Z-m_taille.Z*0);
    glTexCoord2d(m_taille.X*2/mosaic,m_taille.Z*2/mosaic);    glVertex3d(m_end.X+m_taille.X,m_end.Y-m_taille.Y,m_end.Z+m_taille.Z*2);

    glNormal3d(-1.0,0.0,0.0);
    glTexCoord2d(0,m_taille.Z*2/mosaic);               glVertex3d(m_end.X-m_taille.X,m_end.Y+m_taille.Y,m_end.Z+m_taille.Z*2);
    glTexCoord2d(0,0);                          glVertex3d(m_start.X-m_taille.X,m_start.Y+m_taille.Y,m_start.Z-m_taille.Z*0);
    glTexCoord2d(m_taille.Y*2/mosaic,0);               glVertex3d(m_start.X-m_taille.X,m_start.Y-m_taille.Y,m_start.Z-m_taille.Z*0);
    glTexCoord2d(m_taille.Y*2/mosaic,m_taille.Z*2/mosaic);    glVertex3d(m_end.X-m_taille.X,m_end.Y-m_taille.Y,m_end.Z+m_taille.Z*2);



    glNormal3d(0.0,0.0,1.0);
    glTexCoord2d(0,m_taille.X*2/mosaic);               glVertex3d(m_end.X+m_taille.X,m_end.Y+m_taille.Y,m_end.Z+m_taille.Z*2);
    glTexCoord2d(0,0);                          glVertex3d(m_end.X+m_taille.X,m_end.Y+m_taille.Y,m_end.Z+m_taille.Z*2);
    glTexCoord2d(m_taille.Y*2/mosaic,0);               glVertex3d(m_end.X+m_taille.X,m_end.Y-m_taille.Y,m_end.Z+m_taille.Z*2);
    glTexCoord2d(m_taille.Y*2/mosaic,m_taille.X*2/mosaic);    glVertex3d(m_end.X+m_taille.X,m_end.Y-m_taille.Y,m_end.Z+m_taille.Z*2);



    glNormal3d(0.0,0.0,-1.0);
    glTexCoord2d(0,m_taille.X*2/mosaic);               glVertex3d(m_start.X+m_taille.X,m_start.Y+m_taille.Y,m_start.Z-m_taille.Z*0);
    glTexCoord2d(m_taille.Y*2/mosaic,m_taille.X*2/mosaic);    glVertex3d(m_start.X+m_taille.X,m_start.Y-m_taille.Y,m_start.Z-m_taille.Z*0);
    glTexCoord2d(m_taille.Y*2/mosaic,0);               glVertex3d(m_start.X-m_taille.X,m_start.Y-m_taille.Y,m_start.Z-m_taille.Z*0);
    glTexCoord2d(0,0);                          glVertex3d(m_start.X-m_taille.X,m_start.Y+m_taille.Y,m_start.Z-m_taille.Z*0);

    glEnd();

    glPopMatrix();
}



