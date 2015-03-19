#include "Sprite.h"



Sprite::Sprite()
{
    m_frames.clear();
    m_current_frame=0;
    m_vitesse=2;
    m_nextFrame.reset();
    m_taille=Vector3D(1,1,1);
    m_chemin="";
    m_camerapos=Vector3D(0,0,0);
    angleZ=0;
    goRota=true;
}


void Sprite::loadSprite(string chemin)
{
    cerr << "Chargement du sprite " << chemin << endl;
    m_frames.clear();
    m_chemin=chemin;

    DIR *dir;
    struct dirent *lecture;
    std::string en_cours="";

    char* tempchemin=stringtochar(chemin);
    dir = opendir(tempchemin);
    delete tempchemin;
    tempchemin=NULL;

    while ((lecture = readdir(dir)))
    {
        if(strstr(lecture->d_name,".png")!=NULL || strstr(lecture->d_name,".png")!=NULL)
        {
            en_cours=chemin;
            en_cours+=lecture->d_name;
            m_frames.push_back(new Texture());
            m_frames[m_frames.size()-1]->load(en_cours);
            cerr << "frame " << en_cours << endl;
        }
    }
    cerr << endl;
    m_current_frame=myIntRand(0,m_frames.size()-1);
}

void Sprite::update()
{
    //timer to next frame
    m_nextFrame.couler();
    if(m_nextFrame.ecouler(200.0/m_vitesse))
    {
        m_current_frame++;
        if(m_current_frame>=(int)m_frames.size())
            m_current_frame=0;
        m_nextFrame.reset();
    }
    //update angle Z
}
void Sprite::setPositions(Vector3D campos, Vector3D pos)
{
    m_camerapos=campos;
    angleZ=90-atan((pos.X-campos.X)/(pos.Y-campos.Y))*180/3.14;
    //cerr << " sprite adjusté" << angleZ << endl;
}

void Sprite::display()
{
    glDisable(GL_CULL_FACE);
    if(m_frames[m_current_frame]!=NULL)
        m_frames[m_current_frame]->bind();

    //glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glColor4f(1.0,1.0,1.0,1.0);
    if(goRota)
        glRotated(angleZ,0,0,1);

    glBegin(GL_QUADS);
    /*glTexCoord2d(0,1);  glVertex3d(0,m_taille.Y,m_taille.Z*2);
    glTexCoord2d(0,0);  glVertex3d(0,m_taille.Y,-m_taille.Z/2);
    glTexCoord2d(1,0);  glVertex3d(0,-m_taille.Y,-m_taille.Z/2);
    glTexCoord2d(1,1);  glVertex3d(0,-m_taille.Y,m_taille.Z*2);*/

    glTexCoord2d(0,1);  glVertex3d(0,m_taille.Y,m_taille.Z*2+m_taille.Z/2);
    glTexCoord2d(0,0);  glVertex3d(0,m_taille.Y,0);
    glTexCoord2d(1,0);  glVertex3d(0,-m_taille.Y,0);
    glTexCoord2d(1,1);  glVertex3d(0,-m_taille.Y,m_taille.Z*2+m_taille.Z/2);
    glEnd();

    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
}
bool Sprite::getGoRota()
{
    return goRota;
}
void Sprite::setGoRota(bool r)
{
    goRota=r;
}
string Sprite::getChemin()
{
    return m_chemin;
}

void Sprite::setTaille(Vector3D t)
{
    m_taille=t;
}

Vector3D Sprite::getTaille()
{
    return m_taille;
}
