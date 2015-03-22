#include "Lava.h"
#include "Video.h"


Lava::Lava()
{
    m_texture=NULL;
    m_transparency=true;
    m_block=false;
    m_blur=true;
    mosaic=7*2;
    m_speed=0;
    txtcord=Vector3D(0,0,0);

    nextLoopSoundTime=0;

    loopSound="../data/sounds/lava_loop.mp3";
    bubbleSound="../data/sounds/lavabubble.wav";
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

    nextBubbleSoundTime=1000;

    if(Gsounds::getInstance()->getSound(loopSound)!=NULL)
    {
        nextLoopSoundTime=Gsounds::getInstance()->getSound(loopSound)->getLength();
        cerr<<"nextLoopSoundTime: "<<nextLoopSoundTime<<endl;
    }

    //blur
	BlurTexture = EmptyTexture();// Create Our Empty Texture
}


void Lava::update(double functionTime)
{
    //going up
    m_size.Z+=m_speed*functionTime/10;

    //sounds
    loopSoundTime.couler();
    if(nextLoopSoundTime!=0 && loopSoundTime.ecouler(nextBubbleSoundTime))
    {
        loopSoundTime.reset();
        if(Gsounds::getInstance()->getSound(loopSound)!=NULL)
        {
            Gsounds::getInstance()->getSound(loopSound)->setPos((m_position+Vector3D(0,0,m_size.Z*2)).toLeft());
            Gsounds::getInstance()->play(loopSound,1,20,140);
        }
    }
    bubbleSoundTime.couler();
    if(bubbleSoundTime.ecouler(nextBubbleSoundTime))
    {
        bubbleSoundTime.reset();
        nextBubbleSoundTime=myIntRand(1000,3000);
        if(Gsounds::getInstance()->getSound(bubbleSound)!=NULL)
        {
            Gsounds::getInstance()->getSound(bubbleSound)->setPos(
                (Vector3D(myIntRand(0,floor(m_size.X*2)),myIntRand(0,floor(m_size.X*2)),-1)+
                 Vector3D(-m_size.X,-m_size.Y,m_size.Z*2)).toLeft());

            Gsounds::getInstance()->play(bubbleSound,1,30,100);
        }
    }

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

GLuint Lava::EmptyTexture()// Create An Empty Texture
{
	GLuint txtnumber;// Texture ID
	unsigned int* data;// Stored Data

	// Create Storage Space For Texture Data (128x128x4)
	data = (unsigned int*)new GLuint[((128 * 128)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((128 * 128)* 4 * sizeof(unsigned int)));// Clear Storage Memory

	glGenTextures(1, &txtnumber);// Create 1 Texture
	glBindTexture(GL_TEXTURE_2D, txtnumber);// Bind The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 128, 128, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);// Build Texture Using Information In data
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete [] data;// Release data
    data=NULL;

	return txtnumber;// Return The Texture ID
}

void Lava::action(int type, Object* o)
{
         //nehe 36
    int border=128;
	glViewport(0,0,border,border);

	draw();

	glBindTexture(GL_TEXTURE_2D,BlurTexture);
	// Copy Our ViewPort To The Blur Texture (From 0,0 To 128,128... No Border)
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, border, border, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5);// Set The Clear Color To Medium Blue
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear The Screen And Depth Buffer
	glViewport(0,0,Video::getInstance()->getWidth(),Video::getInstance()->getHeight());
}

void Lava::drawBlur()
{
    double times=5;
    double inc=0.04f;

    double m_larg=Video::getInstance()->getWidth();
    double m_haut=Video::getInstance()->getHeight();
    m_larg=1;
    m_haut=1;

	float spost = 0.0f;// Starting Texture Coordinate Offset
	float alphainc = 0.9f / times;// Fade Speed For Alpha Blending
	float alpha = 0.2f;

	// Disable AutoTexture Coordinates
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

    glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D,BlurTexture);


	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,1,1,0,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();


	alphainc = alpha / times;// alphainc=0.2f / Times To Render Blur
	//enleve premier rayon "directement" sur le soleil
    spost += inc;//Gradually Increase spost (Zooming Closer To Texture Center)
    alpha = alpha - alphainc;//Gradually Decrease alpha (Gradually Fading Image Out)

	glBegin(GL_QUADS);
    for (int num = 0;num < times-1;num++)
    {
        if(num!=4)//tres verkrackt, pour eviter que le ciel "devienne blanc" quand on regarde le soleil
        {
            glColor4f(1.0f, 1.0f, 1.0f, alpha);
            glTexCoord2f(0+spost,1-spost);
            glVertex2f(0,0);

            glTexCoord2f(0+spost,0+spost);
            glVertex2f(0,m_haut);

            glTexCoord2f(1-spost,0+spost);
            glVertex2f(m_larg,m_haut);

            glTexCoord2f(1-spost,1-spost);
            glVertex2f(m_larg,0);
        }

        spost += inc;//Gradually Increase spost (Zooming Closer To Texture Center)
        alpha = alpha - alphainc;//Gradually Decrease alpha (Gradually Fading Image Out)
    }
	glEnd();

    glMatrixMode(GL_PROJECTION );
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D,0);
}


void Lava::draw()
{

    //lava
    const Vector3D m_taille=m_size;

    glColor3ub(255,255,255);

    if(m_texture!=NULL)
        m_texture->bind(1);

    Lighting::getInstance()->glDisableLighting();

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
    Lighting::getInstance()->glEnableLighting();
}



