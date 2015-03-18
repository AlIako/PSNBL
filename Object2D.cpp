#include "Object2D.h"


Object2D::Object2D()
{
    m_texture=NULL;
    m_position=Vector3D(0.5,0.5,0);
    m_size=Vector3D(0.1,0.1,0);
    m_name="object2D";

    m_hasText=false;


    m_r=255;
    m_g=255;
    m_b=255;
    m_alpha=1;
}




void Object2D::draw()
{
    if(m_hasText)
    {
        m_text.setX(m_position.X);
        m_text.setY(m_position.Y);

        m_text.draw(m_r,m_g,m_b);
    }

    if(m_texture!=NULL)
    {
        Video::getInstance()->matrixOrtho2D();

        Lighting::getInstance()->glDisableLighting();
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        m_texture->bind(true);

        glColor4ub(m_r,m_g,m_b,255*m_alpha);
        glBegin(GL_QUADS);
            glTexCoord2d(0,0);    glVertex2d(m_position.X,m_position.Y);
            glTexCoord2d(0,1);    glVertex2d(m_position.X,m_position.Y+m_size.Y);
            glTexCoord2d(1,1);    glVertex2d(m_position.X+m_size.X,m_position.Y+m_size.Y);
            glTexCoord2d(1,0);    glVertex2d(m_position.X+m_size.X,m_position.Y);
        glEnd();


        glDisable(GL_BLEND);

        glEnable(GL_DEPTH_TEST);
        Video::getInstance()->matrixProjection();
    }
}

void Object2D::ini()
{

}


void Object2D::update(double functionTime)
{

}



void Object2D::addText(string txt)
{
    m_hasText=true;
    m_text.setTexte(txt);
    m_text.ini(Video::getInstance()->getWidth(),Video::getInstance()->getHeight(),TextManager::getInstance()->getFont());
    //cerr<<"test1"<<endl;
    //m_text.draw(255,255,255);
    //cerr<<"test2"<<endl;
}

void Object2D::setText(string txt)
{
    m_text.setTexte(txt);
}



