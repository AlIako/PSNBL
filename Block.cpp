#include "Block.h"



Block::Block()
{
    m_texture=NULL;
    mosaic=4;
    divided=false;

    m_hookable=true;
    m_name="block";
}

void Block::ini()
{
    m_type="block";
    if(GTexture::getInstance())
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
        mosaic=16;
        if(m_name=="finalBlock")
        {
            path="../data/textures/redrock.png";
            mosaic=4;
        }
        if(m_name=="noHookBlock")
        {
            path="../data/textures/metal.png";
            m_hookable=false;
            mosaic=4;
        }
        if(m_name=="jumpBlock")
        {
            path="../data/textures/carpet_red.jpg";
            m_hookable=false;
            m_block=false;
            mosaic=4;
        }
        char* tempPath=stringtochar(path);

        if(!m_texture)
            m_texture=GTexture::getInstance()->addGetTexture(tempPath);

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
    if(m_visible)
    {
        const Vector3D m_taille=m_size;
        Lighting::getInstance()->glEnableLighting();

        if(m_selected)
            drawBox();

        glColor4ub(255,255,255,255);

        if(m_texture!=NULL)
            m_texture->bind();


        glPushMatrix();
        glTranslated(m_position.X,m_position.Y,m_position.Z);
        //glRotated(m_rotation.Z,0,0,1);

        if(m_name=="jumpBlock")
        {
            Lighting::getInstance()->glDisableLighting();
            glTranslated(0,0,m_taille.Z*2*0);
            glDisable(GL_CULL_FACE);
            m_texture->bind();
            glBlendFunc(GL_SRC_ALPHA,GL_ONE);
            glEnable(GL_BLEND);
            GLUquadric* params = gluNewQuadric();
            gluQuadricTexture(params,GL_TRUE);

            glRotated(m_rotation.Z-180,0,0,1);
            gluCylinder(params,m_size.X*1,m_taille.X*1.5,m_taille.Z*1.5,5,5);
            glRotated(-2*m_rotation.Z,0,0,1);
            gluCylinder(params,m_taille.X*1.2,m_taille.X*2.3,m_taille.Z*0.6,5,5);
            m_rotation.Z+=ft;
            gluDeleteQuadric(params);

            glDisable(GL_BLEND);
            //glEnable(GL_CULL_FACE);
        }
        else
        {
            glEnable(GL_CULL_FACE);
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

            glDisable(GL_CULL_FACE);

        }



        glPopMatrix();

        glColor3ub(255,255,255);

        Lighting::getInstance()->glEnableLighting();
    }
}

void Block::action(int type, Object* o)
{
    if(type==100)
        drawRight();
    else if(type==101)
        drawFront();
    else if(type==102)
        drawLeft();
    else if(type==103)
        drawBack();
    else if(type==104)
        drawTop();
    else if(type==105)
        drawBot();
}

void Block::drawRight()
{
    glNormal3d(0.0,1.0,0.0);
    glTexCoord2d(1,0);    glVertex3d(m_size.X,m_size.Y,m_size.Z);
    glTexCoord2d(1,1);    glVertex3d(m_size.X,m_size.Y,-m_size.Z);
    glTexCoord2d(0,1);    glVertex3d(-m_size.X,m_size.Y,-m_size.Z);
    glTexCoord2d(0,0);    glVertex3d(-m_size.X,m_size.Y,m_size.Z);
}
void Block::drawFront()
{
    glNormal3d(1.0,0.0,0.0);
    glTexCoord2d(1,0);    glVertex3d(m_size.X,-m_size.Y,m_size.Z);
    glTexCoord2d(1,1);    glVertex3d(m_size.X,-m_size.Y,-m_size.Z);
    glTexCoord2d(0,1);    glVertex3d(m_size.X,m_size.Y,-m_size.Z);
    glTexCoord2d(0,0);    glVertex3d(m_size.X,m_size.Y,m_size.Z);
}
void Block::drawLeft()
{
    glNormal3d(0.0,-1.0,0.0);
    glTexCoord2d(0,1);    glVertex3d(-m_size.X,-m_size.Y,m_size.Z);
    glTexCoord2d(0,0);    glVertex3d(-m_size.X,-m_size.Y,-m_size.Z);
    glTexCoord2d(1,0);    glVertex3d(m_size.X,-m_size.Y,-m_size.Z);
    glTexCoord2d(1,1);    glVertex3d(m_size.X,-m_size.Y,m_size.Z);
}
void Block::drawBack()
{
    glNormal3d(-1.0,0.0,0.0);
    glTexCoord2d(0,1);    glVertex3d(-m_size.X,m_size.Y,m_size.Z);
    glTexCoord2d(0,0);    glVertex3d(-m_size.X,m_size.Y,-m_size.Z);
    glTexCoord2d(1,0);    glVertex3d(-m_size.X,-m_size.Y,-m_size.Z);
    glTexCoord2d(1,1);    glVertex3d(-m_size.X,-m_size.Y,m_size.Z);
}
void Block::drawTop()
{
    glNormal3d(0.0,0.0,1.0);
    glTexCoord2d(0,1);    glVertex3d(m_size.X,m_size.Y,m_size.Z);
    glTexCoord2d(0,0);    glVertex3d(-m_size.X,m_size.Y,m_size.Z);
    glTexCoord2d(1,0);    glVertex3d(-m_size.X,-m_size.Y,m_size.Z);
    glTexCoord2d(1,1);    glVertex3d(m_size.X,-m_size.Y,m_size.Z);
}
void Block::drawBot()
{
    glNormal3d(0.0,0.0,-1.0);
    glTexCoord2d(0,1);    glVertex3d(m_size.X,m_size.Y,-m_size.Z);
    glTexCoord2d(1,1);    glVertex3d(m_size.X,-m_size.Y,-m_size.Z);
    glTexCoord2d(1,0);    glVertex3d(-m_size.X,-m_size.Y,-m_size.Z);
    glTexCoord2d(0,0);    glVertex3d(-m_size.X,m_size.Y,-m_size.Z);
}

string Block::writeObj()
{

    std::ostringstream oss;

    oss << Object::writeObj();

    oss<<" name: " << m_name;

    return oss.str();
}

