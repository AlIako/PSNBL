#include "Gmodel.h"


Gmodel* Gmodel::m_instance = new Gmodel();


Gmodel* Gmodel::getInstance()
{
    return m_instance;
}



Gmodel::Gmodel()
{
    m_texture1=NULL;
    m_texture2=NULL;
    m_texture3=NULL;
    m_texture4=NULL;
    m_texture5=NULL;
}

void Gmodel::reini()
{
    delAll();
}

void Gmodel::drawSculpture(std::string sculpt)
{
    if(sculpt=="rocket")//rocket
    {
        if(m_texture1==NULL)
        {
            GTexture::getInstance()->addTexture("data/textures/rocket/6.jpg");
            m_texture1=GTexture::getInstance()->getTexture("data/textures/rocket/6.jpg");
            GTexture::getInstance()->addTexture("data/textures/rocket/5.jpg");
            m_texture2=GTexture::getInstance()->getTexture("data/textures/rocket/5.jpg");
            GTexture::getInstance()->addTexture("data/textures/rocket/4.jpg");
            m_texture3=GTexture::getInstance()->getTexture("data/textures/rocket/4.jpg");
            GTexture::getInstance()->addTexture("data/textures/rocket/3.jpg");
            m_texture4=GTexture::getInstance()->getTexture("data/textures/rocket/3.jpg");
        }
        glDisable(GL_CULL_FACE);
        glScalef(.5,.5,.5);
        m_texture1->bind();
        glRotated(90,0,1,0);
        GLUquadric* params = gluNewQuadric();
        gluQuadricTexture(params,GL_TRUE);
        gluCylinder(params,0.50,0,1.60,20,1);
        m_texture3->bind();
        glTranslated(0,0,-1.05);
        gluCylinder(params,0.15,0.50,1.05,20,1);
        m_texture4->bind();
        glTranslated(0,0,-0.25);
        gluCylinder(params,0.30,0.15,0.25,20,1);
        m_texture2->bind();
        gluDisk(params,0,0.30,15,1);
        gluDeleteQuadric(params);
        glEnable(GL_CULL_FACE);
    }
    else if(sculpt=="tir")//tir
    {
        if(m_texture5==NULL)
        {
            GTexture::getInstance()->addTexture("data/textures/rocket/bullet.png");
            m_texture5=GTexture::getInstance()->getTexture("data/textures/rocket/bullet.png");
        }
        int sc=7;
        glRotated(-90,0,0,1);
        glRotated(-10,1,0,0);
        glDisable(GL_CULL_FACE);
        m_texture5->bind();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
        glTexCoord2d(1,1);     glVertex3d(-.5/sc,-1.5*2/sc,0);
        glTexCoord2d(0,1);     glVertex3d(-.5/sc,1.5*2/sc,0);
        glTexCoord2d(0,0);     glVertex3d(.5/sc,1.5*2/sc,0);
        glTexCoord2d(1,0);     glVertex3d(.5/sc,-1.5*2/sc,0);
        glEnd();
        glDisable(GL_BLEND);
        glEnable(GL_CULL_FACE);
    }
}

void Gmodel::addSprite(std::string chemin)
{
    bool djala=false;
    for(unsigned int i=0;i<sprites.size();i++)
        if(sprites[i]->getChemin()==chemin)
            djala=true;

    if(!djala)
    {
        sprites.push_back(new Sprite());

        char* tempchemin=stringtochar(chemin);
        sprites[sprites.size()-1]->loadSprite(tempchemin);
        delete tempchemin;
        tempchemin=NULL;
    }
}
void Gmodel::addMesh(std::string chemin)
{
    bool djala=false;
    for(unsigned int i=0;i<meshes.size();i++)
        if(meshes[i]->getRepertoire()==chemin)
            djala=true;

    if(!djala)
    {
        meshes.push_back(new CMesh());

        char* tempchemin=stringtochar(chemin);
        meshes[meshes.size()-1]->loadMesh(tempchemin,&loader);
        delete tempchemin;
        tempchemin=NULL;
    }
}
void Gmodel::addMD2(std::string chemin)
{
    bool djala=false;
    for(unsigned int i=0;i<md2models.size();i++)
        if(md2models[i]!=NULL && md2models[i]->repertoire==chemin)
            djala=true;

    if(!djala)
    {
        md2models.push_back(new md2_model_t());

        char* tempchemin=stringtochar(chemin);
        md2models[md2models.size()-1]->ReadMD2Model(tempchemin);
        delete tempchemin;
        tempchemin=NULL;
    }
}

Sprite* Gmodel::getSprite(std::string nom)
{
    for(unsigned int i=0;i<sprites.size();i++)
    {
        if(sprites[i]->getChemin()==nom)
            return sprites[i];
    }
    return NULL;
}
CMesh* Gmodel::getMesh(std::string nom)
{
    for(unsigned int i=0;i<meshes.size();i++)
    {
        if(meshes[i]->getRepertoire()==nom)
            return meshes[i];
    }
    return NULL;
}
md2_model_t* Gmodel::getMD2(std::string nom)
{
    md2_model_t* temp=NULL;
    for(unsigned int i=0;i<md2models.size();i++)
    {
        if(md2models[i]->repertoire==nom)
        {
            temp= md2models[i];
        }
    }
    return temp;
}
void Gmodel::delAll()
{
   /* for(unsigned int i=0;i<md2models.size();i++)
        delete md2models[i];
    for(unsigned int i=0;i<meshes.size();i++)
        delete meshes[i];
    for(unsigned int i=0;i<sprites.size();i++)
        delete sprites[i];*/
    md2models.clear();
    meshes.clear();
    sprites.clear();
}
