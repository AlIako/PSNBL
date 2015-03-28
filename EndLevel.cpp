#include "EndLevel.h"

EndLevel::EndLevel()
{
    m_type="endlevel";
    m_name=m_type;
    m_hookable=false;
    m_block=false;
    dirmov=Vector3D(0,-1,0);
    txtcord=Vector3D(0,0,0);
    //m_physical=false;
}




void EndLevel::ini()
{
    m_hookable=false;
    m_block=false;

    if(!m_texture)
        m_texture=GTexture::getInstance()->addGetTexture("../data/textures/aura.png");
}


void EndLevel::draw()
{
    if(m_visible)
    {

        txtcord+=dirmov*ft;

        const Vector3D m_taille=m_size;
        double mosaic=1;
        Lighting::getInstance()->glEnableLighting();

        if(m_selected)
            drawBox();

        glColor4ub(255,255,255,255);

        if(m_texture!=NULL)
            m_texture->bind();


        glPushMatrix();
        glTranslated(m_position.X,m_position.Y,m_position.Z);

        Lighting::getInstance()->glDisableLighting();
        glTranslated(0,0,m_taille.Z*2*0);
        glDisable(GL_CULL_FACE);
        m_texture->bind();
        glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        glEnable(GL_BLEND);

        glBegin(GL_QUADS);

        glNormal3d(0.0,1.0,0.0);
        glTexCoord2d(0-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);               glVertex3d(m_taille.X,m_taille.Y,m_taille.Z*2);
        glTexCoord2d(0-txtcord.Y/100,0-txtcord.X/100);                              glVertex3d(m_taille.X,m_taille.Y,0);
        glTexCoord2d(m_taille.X*2/mosaic-txtcord.Y/100,0-txtcord.X/100);               glVertex3d(-m_taille.X,m_taille.Y,0);
        glTexCoord2d(m_taille.X*2/mosaic-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);                          glVertex3d(-m_taille.X,m_taille.Y,m_taille.Z*2);

        glNormal3d(1.0,0.0,0.0);
        glTexCoord2d(0-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);               glVertex3d(m_taille.X,-m_taille.Y,m_taille.Z*2);
        glTexCoord2d(0-txtcord.Y/100,0-txtcord.X/100);    glVertex3d(m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(m_taille.Y*2/mosaic-txtcord.Y/100,0-txtcord.X/100);               glVertex3d(m_taille.X,m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(m_taille.Y*2/mosaic-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);                          glVertex3d(m_taille.X,m_taille.Y,m_taille.Z*2);

        glNormal3d(0.0,-1.0,0.0);
        glTexCoord2d(0-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);               glVertex3d(-m_taille.X,-m_taille.Y,m_taille.Z*2);
        glTexCoord2d(0-txtcord.Y/100,0-txtcord.X/100);                          glVertex3d(-m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(m_taille.X*2/mosaic-txtcord.Y/100,0-txtcord.X/100);               glVertex3d(m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(m_taille.X*2/mosaic-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);    glVertex3d(m_taille.X,-m_taille.Y,m_taille.Z*2);

        glNormal3d(-1.0,0.0,0.0);
        glTexCoord2d(0-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);               glVertex3d(-m_taille.X,m_taille.Y,m_taille.Z*2);
        glTexCoord2d(0-txtcord.Y/100,0-txtcord.X/100);                          glVertex3d(-m_taille.X,m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(m_taille.Y*2/mosaic-txtcord.Y/100,0-txtcord.X/100);               glVertex3d(-m_taille.X,-m_taille.Y,-m_taille.Z*0);
        glTexCoord2d(m_taille.Y*2/mosaic-txtcord.Y/100,m_taille.Z*2/mosaic-txtcord.X/100);    glVertex3d(-m_taille.X,-m_taille.Y,m_taille.Z*2);
        glEnd();


        glDisable(GL_BLEND);


        glPopMatrix();

        glColor3ub(255,255,255);

        Lighting::getInstance()->glEnableLighting();
    }
}


void EndLevel::action(int type, Object* o)
{
    //m_life=0;
}
