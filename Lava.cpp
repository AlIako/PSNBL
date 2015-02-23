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
    if(GTexture::getInstance())
    {
        GTexture::getInstance()->addTexture("../data/textures/lava.png");
        m_texture=GTexture::getInstance()->getTexture("../data/textures/lava.png");
    }

    dampvalue.setParameter(15, 2);
    dampvalue = 2;

    //bubbles
    m_bubbles.resize(100);
    m_steam.resize(150);




    Object::ini();
}


void Lava::update(double functionTime)
{
    m_size.Z+=m_speed*functionTime/10;

    //text value damping
    dampvalue.update(functionTime/10.0);
    txtcord.X += 0*dampvalue/5;
    txtcord.Y += 0*dampvalue/5;

    if(dampvalue>=1)
        dampvalue = -2;
    if(dampvalue<=-1)
        dampvalue = 2;


    //bubbles
    for(unsigned int i=0;i<m_bubbles.size();i++)
    {
        m_bubbles[i].update(functionTime);
        if(m_bubbles[i].getLife()<=0)
        {
            m_bubbles[i].setTexture(m_texture);
            m_bubbles[i].setSize(Vector3D(1,1,1));
            m_bubbles[i].ini();
            m_bubbles[i].timeToPop=myIntRand(2000,12000);
            m_bubbles[i].speedDie=0.03+0*myIntRand(1,10)/2000.0;
            m_bubbles[i].speedSize=myIntRand(1,10)/1000.0;
            m_bubbles[i].setPos(Vector3D(myIntRand(0,floor(m_size.X*2)),myIntRand(0,floor(m_size.X*2)),-1)+
                                Vector3D(-m_size.X,-m_size.Y,m_size.Z*2));//randomize X Y position
        }
        m_bubbles[i].setPos(Vector3D(m_bubbles[i].getPos().X,m_bubbles[i].getPos().Y,m_size.Z*2-1));//lava goes up; update Z
    }
    for(unsigned int i=0;i<m_steam.size();i++)
    {
        m_steam[i].update(functionTime);
        if(m_steam[i].getLife()<=0)
        {
            m_steam[i].setTexture(m_texture);
            m_steam[i].setSize(Vector3D(0.1,0.1,0.1));
            m_steam[i].ini();
            m_steam[i].timeToPop=-1;
            m_steam[i].speedDie=myIntRand(1,5)/300.0;
            m_steam[i].speedSize=0;
            m_steam[i].setSize(Vector3D(myIntRand(1,5)/10.0,0,0));
            m_steam[i].goingUp=true;
            m_steam[i].setPos(Vector3D(myIntRand(0,floor(m_size.X*2)),myIntRand(0,floor(m_size.X*2)),-1)+
                                Vector3D(-m_size.X,-m_size.Y,m_size.Z*2));//randomize X Y position
        }
        m_steam[i].setPos(Vector3D(m_steam[i].getPos().X,m_steam[i].getPos().Y,m_size.Z*2-1));//lava goes up; update Z
    }
}


void Lava::draw()
{

    //lava
    const Vector3D m_taille=m_size;

    glColor3ub(255,255,255);

    if(m_texture!=NULL)
        m_texture->bind();


    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    //glEnable(GL_BLEND);
    glPushMatrix();
    glTranslated(m_position.X,m_position.Y,m_position.Z);



    Vector3D savetxtcord=txtcord;
    int duplicate=1;
    double zDif=2;
    glTranslated(0,0,-zDif*duplicate);
    for(int i=0;i<duplicate;i++)
    {
        glTranslated(0,0,zDif);
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
        txtcord*=-1;
    }
    txtcord=savetxtcord;


    //bubble
    glTranslated(-txtcord.X/10,txtcord.Y/10,0);
    for(unsigned int i=0;i<m_bubbles.size();i++)
        m_bubbles[i].draw();
    for(unsigned int i=0;i<m_steam.size();i++)
        m_steam[i].draw();

    glPopMatrix();


    glDisable(GL_BLEND);
}



