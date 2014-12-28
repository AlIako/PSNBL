#include "Block.h"



Block::Block()
{
    m_texture=NULL;
    mosaic=4;
}

void Block::ini()
{
    m_type="block";
    if(gtext!=NULL)
    {
        string path="../data/textures/bedrock.png";

        /*int randTexture=myIntRand(0,300);
        if(randTexture>200)
            path="../data/textures/cubes_squares.jpg";
        else if(randTexture>100)
            path="../data/textures/cubes_circles.jpg";
        else if(randTexture>100)
            path="../data/textures/cubes_triangles.jpg";
        */
        char* tempPath=stringtochar(path);
        gtext->addTexture(tempPath);
        m_texture=gtext->getTexture(tempPath);
        delete tempPath;
    }

    Object::ini();

    m_r=myIntRand(0,255);
    m_g=myIntRand(0,255);
    m_b=myIntRand(0,255);

    m_r=255;
    m_g=255;
    m_b=255;
}


void Block::draw()
{
    const Vector3D m_taille=m_size;

    glColor3ub(m_r,m_g,m_b);

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



