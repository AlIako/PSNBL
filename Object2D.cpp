#include "Object2D.h"


Object2D::Object2D()
{
    m_texture=NULL;
    m_position=Vector3D(0.5,0.5,0);
    m_size=Vector3D(0.1,0.1,0);

    m_clicable=false;
    m_hover=false;
    m_clicked=false;
}




void Object2D::draw()
{
    Video::getInstance()->matrixOrtho2D();

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    if(m_texture)
        m_texture->bind();

    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);    glVertex2d(m_position.X,m_position.Y);
        glTexCoord2d(0,1);    glVertex2d(m_position.X,m_position.Y+m_size.Y);
        glTexCoord2d(1,1);    glVertex2d(m_position.X+m_size.X,m_position.Y+m_size.Y);
        glTexCoord2d(1,0);    glVertex2d(m_position.X+m_size.X,m_position.Y);
    glEnd();



    Video::getInstance()->matrixProjection();
}



void Object2D::update(double functionTime)
{

}


void Object2D::updateCursor(Vector3D pos)
{

}


void Object2D::clic(Vector3D pos)
{

}





