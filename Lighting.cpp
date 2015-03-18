#include "Lighting.h"


Lighting* Lighting::m_instance = new Lighting();


Lighting* Lighting::getInstance()
{
    return m_instance;
}




Lighting::Lighting()
{
    lumieres.clear();
    m_active=false;
}

void Lighting::shineAmbiant()
{
    if(m_active)
    {
        glShadeModel(GL_SMOOTH);
        //glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

        Lighting::getInstance()->glEnableLighting();
        glEnable(GL_LIGHT0);

        //GLfloat global_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
        GLfloat global_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };

        GLfloat lmodel_ambient[]= {0.2f,0.2f,0.2f,1.0f};			// And More Ambient Light
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);		// Set The Ambient Light Model

        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);		// Set The Global Ambient Light Model

        GLfloat zero[4]	= {.0f,.0f,.0f,0.f};
        //GLfloat midl[4]	= {.3f,.3f,.3f,1.f};
        GLfloat midl[4]	= {1.0f,1.0f,1.0f,1.f};
        //GLfloat ambientLight[] = { 0.4f, 0.4f, 0.4f, 1.0f };
        GLfloat ambientLight[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        //GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
        GLfloat diffuseLight[] = { 0.0f, 0.0f, 0.0, 1.0f };
        //GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat specularLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
        glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,.000001f);
        glMaterialfv(GL_FRONT, GL_AMBIENT,  midl);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,  midl);
        glMaterialfv(GL_FRONT, GL_SPECULAR, zero);
        glMaterialfv(GL_FRONT, GL_EMISSION, zero);
        glMateriali(GL_FRONT, GL_SHININESS, 256);
    }
}

void Lighting::shineAll()
{
    if(m_active)
    {
        for(unsigned int i=0;i<lumieres.size();i++)
        {
            GLfloat ambientLight[] = { lumieres[i].r/255.0, lumieres[i].g/255.0, lumieres[i].b/255.0, lumieres[i].alpha };
            GLfloat diffuseLight[] =  { lumieres[i].r/255.0, lumieres[i].g/255.0, lumieres[i].b/255.0, lumieres[i].alpha };
            GLfloat specularLight[] = { 0.0f, 0.0f, 0.0, 1.0f };
            GLfloat LightPos[4] = {lumieres[i].x,lumieres[i].y,lumieres[i].z,1};
            double atenuation=lumieres[i].at;
            switch(i)
            {
                case 0:
                glEnable(GL_LIGHT1);
                glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
                glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
                glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
                glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,atenuation);
                glLightfv(GL_LIGHT1,GL_POSITION,LightPos);
                break;
                case 1:
                glEnable(GL_LIGHT2);
                glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
                glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
                glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight);
                glLightf(GL_LIGHT2,GL_QUADRATIC_ATTENUATION,atenuation);
                glLightfv(GL_LIGHT2,GL_POSITION,LightPos);
                break;
                case 2:
                glEnable(GL_LIGHT3);
                glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
                glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
                glLightfv(GL_LIGHT3, GL_SPECULAR, specularLight);
                glLightf(GL_LIGHT3,GL_QUADRATIC_ATTENUATION,atenuation);
                glLightfv(GL_LIGHT3,GL_POSITION,LightPos);
                break;
                case 3:
                glEnable(GL_LIGHT4);
                glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuseLight);
                glLightfv(GL_LIGHT4, GL_SPECULAR, specularLight);
                glLightf(GL_LIGHT4,GL_QUADRATIC_ATTENUATION,atenuation);
                glLightfv(GL_LIGHT4,GL_POSITION,LightPos);
                break;
                case 4:
                glEnable(GL_LIGHT5);
                glLightfv(GL_LIGHT5, GL_AMBIENT, ambientLight);
                glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuseLight);
                glLightfv(GL_LIGHT5, GL_SPECULAR, specularLight);
                glLightf(GL_LIGHT5,GL_QUADRATIC_ATTENUATION,atenuation);
                glLightfv(GL_LIGHT5,GL_POSITION,LightPos);
                break;
                case 5:
                glEnable(GL_LIGHT6);
                glLightfv(GL_LIGHT6, GL_AMBIENT, ambientLight);
                glLightfv(GL_LIGHT6, GL_DIFFUSE, diffuseLight);
                glLightfv(GL_LIGHT6, GL_SPECULAR, specularLight);
                glLightf(GL_LIGHT6,GL_QUADRATIC_ATTENUATION,atenuation);
                glLightfv(GL_LIGHT6,GL_POSITION,LightPos);
                break;
                case 6:
                glEnable(GL_LIGHT7);
                glLightfv(GL_LIGHT7, GL_AMBIENT, ambientLight);
                glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuseLight);
                glLightfv(GL_LIGHT7, GL_SPECULAR, specularLight);
                glLightf(GL_LIGHT7,GL_QUADRATIC_ATTENUATION,atenuation);
                glLightfv(GL_LIGHT7,GL_POSITION,LightPos);
                break;
                default:
                break;
            }
        }
    }
}

void Lighting::glDisableLighting()
{
    if(1)
        glDisable(GL_LIGHTING);
}

void Lighting::glEnableLighting()
{
    if(m_active)
        glEnable(GL_LIGHTING);
}

void Lighting::addLight()
{
    Light l;
    l.x=0;
    l.y=0;
    l.z=0;
    l.r=255;
    l.g=255;
    l.b=255;
    l.alpha=1;
    l.on=true;
    l.at=0.1;
    lumieres.push_back(l);
}

Light Lighting::getLight(unsigned int id)
{
    for(unsigned int i=0;i<lumieres.size();i++)
        if(i==id)
            return lumieres[i];
    return lumieres[0];
}

unsigned int Lighting::getSize()
{
    return lumieres.size();
}

void Lighting::setX(string lequel,double x)
{
    if(lequel=="last")
        lumieres[lumieres.size()-1].x=x;
    else if(lequel=="all")
        for(unsigned int i=0;i<lumieres.size();i++)
            lumieres[i].x=x;
}
void Lighting::setY(string lequel,double y)
{
    if(lequel=="last")
        lumieres[lumieres.size()-1].y=y;
    else if(lequel=="all")
        for(unsigned int i=0;i<lumieres.size();i++)
            lumieres[i].y=y;
}
void Lighting::setZ(string lequel,double z)
{
    if(lequel=="last")
        lumieres[lumieres.size()-1].z=z;
    else if(lequel=="all")
        for(unsigned int i=0;i<lumieres.size();i++)
            lumieres[i].z=z;
}
void Lighting::setR(string lequel,double r)
{
    if(lequel=="last")
        lumieres[lumieres.size()-1].r=r;
    else if(lequel=="all")
        for(unsigned int i=0;i<lumieres.size();i++)
            lumieres[i].r=r;
}
void Lighting::setG(string lequel,double g)
{
    if(lequel=="last")
        lumieres[lumieres.size()-1].g=g;
    else if(lequel=="all")
        for(unsigned int i=0;i<lumieres.size();i++)
            lumieres[i].g=g;
}
void Lighting::setB(string lequel,double b)
{
    if(lequel=="last")
        lumieres[lumieres.size()-1].b=b;
    else if(lequel=="all")
        for(unsigned int i=0;i<lumieres.size();i++)
            lumieres[i].b=b;
}

void Lighting::setAT(string lequel,double at)
{
    if(lequel=="last")
        lumieres[lumieres.size()-1].at=at;
    else if(lequel=="all")
        for(unsigned int i=0;i<lumieres.size();i++)
            lumieres[i].at=at;
}

void Lighting::delAll()
{
    lumieres.clear();
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
    glDisable(GL_LIGHT4);
    glDisable(GL_LIGHT5);
    glDisable(GL_LIGHT6);
    glDisable(GL_LIGHT7);
}
