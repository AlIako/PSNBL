#include "Wall.h"





Wall::Wall()
{
    mosaic=15;
    m_hookable=false;
    divided=true;
}



void Wall::ini()
{
    m_type="wall";
    if(GTexture::getInstance()!=NULL)
    {
        GTexture::getInstance()->addTexture("../data/textures/hellrock_static.png");
        m_texture=GTexture::getInstance()->getTexture("../data/textures/hellrock_static.png");
    }

    Object::ini();

    m_r=255;
    m_g=255;
    m_b=255;

    m_hookable=false;
}


void Wall::draw()
{
    if(m_visible)
    {
        glEnable(GL_CULL_FACE);

        const Vector3D m_taille=m_size;

        glColor4ub(255,255,255,255);

        if(m_texture!=NULL)
            m_texture->bind();


        glPushMatrix();
        glTranslated(m_position.X,m_position.Y,m_position.Z);
        //glRotated(m_rotation.Z,0,0,1);


        glBegin(GL_QUADS);

        int bs=50;
        int bsx=bs;
        int bsy=bs;

        if(m_size.X>m_size.Y)
        {
            //X width
            for(double i=-m_taille.X;i<m_taille.X+bsx;i+=bsx)
            {
                for(double j=0;j<2*m_taille.Z;j+=bs)
                {
                    if(m_position.Y<0)
                    {
                        glNormal3d(0.0,1.0,0.0);
                        glTexCoord2d(1,0);  glVertex3d(i,m_taille.Y,j);
                        glTexCoord2d(1,1);  glVertex3d(i,m_taille.Y,j-bs);
                        glTexCoord2d(0,1);  glVertex3d(i-bsx,m_taille.Y,j-bs);
                        glTexCoord2d(0,0);  glVertex3d(i-bsx,m_taille.Y,j);
                    }

                    if(m_position.Y>0)
                    {
                        glNormal3d(0.0,-1.0,0.0);
                        glTexCoord2d(0,0);  glVertex3d(i-bsx,-m_taille.Y,j);
                        glTexCoord2d(0,1);  glVertex3d(i-bsx,-m_taille.Y,j-bs);
                        glTexCoord2d(1,1);  glVertex3d(i,-m_taille.Y,j-bs);
                        glTexCoord2d(1,0);  glVertex3d(i,-m_taille.Y,j);
                    }



                }
            }
        }

        if(m_size.Y>m_size.X)
        {
            //Y width
            for(double i=-m_taille.Y;i<m_taille.Y+bsy;i+=bsy)
            {
                for(double j=0;j<2*m_taille.Z;j+=bs)
                {
                    if(m_position.X<0)
                    {
                        glNormal3d(1.0,0.0,0.0);
                        glTexCoord2d(1,1);  glVertex3d(m_taille.X,i-bsy,j);
                        glTexCoord2d(1,0);  glVertex3d(m_taille.X,i-bsy,j-bs);
                        glTexCoord2d(0,0);  glVertex3d(m_taille.X,i,j-bs);
                        glTexCoord2d(0,1);  glVertex3d(m_taille.X,i,j);
                    }


                    if(m_position.X>0)
                    {
                        glNormal3d(-1.0,0.0,0.0);
                        glTexCoord2d(0,1);  glVertex3d(-m_taille.X,i,j);
                        glTexCoord2d(0,0);  glVertex3d(-m_taille.X,i,j-bs);
                        glTexCoord2d(1,0);  glVertex3d(-m_taille.X,i-bsy,j-bs);
                        glTexCoord2d(1,1);  glVertex3d(-m_taille.X,i-bsy,j);
                    }

                }
            }
        }
        glEnd();


        glPopMatrix();

        glColor3ub(255,255,255);

        glDisable(GL_CULL_FACE);

        Lighting::getInstance()->glEnableLighting();
    }
}
