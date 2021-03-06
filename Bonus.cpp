#include "Bonus.h"



Bonus::Bonus()
{
    m_type="bonus";
    m_name="bonus";

    m_physical=false;
    m_gravity=false;
    m_block=false;

    m_texture=NULL;
    m_size=Vector3D(1,1,1);
}



void Bonus::ini()
{
    m_type="bonus";
    if(GTexture::getInstance())
    {
        if(m_name=="rez")
        {
            m_texture=GTexture::getInstance()->addGetTexture("../data/textures/blue.jpg");
        }
        else if(m_name=="rope")
        {
            m_texture=GTexture::getInstance()->addGetTexture("../data/textures/rope.jpg");
        }
        else if(m_name=="nextphase")
        {
            m_transparency=true;
            m_texture=GTexture::getInstance()->addGetTexture("../data/textures/redrock.png");
        }
        else if(m_name=="startboss")
        {
            m_transparency=true;
            m_texture=GTexture::getInstance()->addGetTexture("../data/textures/greenrock.png");
        }
        else if(m_name=="health")
        {
            m_texture=GTexture::getInstance()->addGetTexture("../data/textures/carpet_red.jpg");

            meshPath="../data/mesh/vie.obj";
            Gmodel::getInstance()->addMesh(meshPath);
        }
    }

    Object::ini();
}

void Bonus::loseLife(double value)
{
    Object::loseLife(value);
    if(m_name=="rez")
        Gsounds::getInstance()->play("../data/sounds/metal_impact.mp3");
}

void Bonus::update(double functionTime)
{
    m_rotation.Z+=ft;

    Object::update(functionTime);
}

void Bonus::draw()
{
    const Vector3D m_taille=m_size;
    double mosaic=2;

    glColor3ub(255,255,255);

    if(m_texture!=NULL)
        m_texture->bind();


    glPushMatrix();
    glTranslated(m_position.X,m_position.Y,m_position.Z);
    glRotated(m_rotation.Z,0,0,1);

    if(m_name=="rez" || m_name=="rope")
    {
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
    }
    else if(m_name=="nextphase" || m_name=="startboss")
    {
        glTranslated(0,0,1);
        glDisable(GL_CULL_FACE);
        Lighting::getInstance()->glDisableLighting();

        glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glColor4f(1,1,1,0.5);
        GLUquadric* params = gluNewQuadric();
        gluQuadricTexture(params,GL_TRUE);
        gluSphere(params,m_size.X*2,10,10);
        gluDeleteQuadric(params);

        glDisable(GL_BLEND);
        glTranslated(0,0,-1);
    }
    else if(m_name=="health")
    {
        glTranslated(0,0,1);

        double sc=.5;
        //sc=100000;
        glScaled(sc,sc,sc);
        //Gmodel::getInstance()->getMesh("../data/mesh/vie.obj")->draw();

        if(m_texture)
            m_texture->bind();

        Gmodel::getInstance()->getMesh(meshPath)->drawNoTexture();
    }

    glPopMatrix();
}



string Bonus::writeObj()
{

    std::ostringstream oss;

    oss << Object::writeObj();

    oss<<" name: " << m_name;

    return oss.str();
}
