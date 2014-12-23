#include "GTexture.h"


GTexture::GTexture()
{
    m_textures.clear();
    //m_textures.push_back(new Texture("data/red.jpg"));
    lastBind=NULL;
}

void GTexture::loadAll()
{
    m_textures.clear();

    DIR *dir;
    struct dirent *lecture;
    std::string en_cours="";
    dir = opendir("../data/textures");
    while ((lecture = readdir(dir)))
    {
        if(strstr(lecture->d_name,".JPEG")!=NULL || strstr(lecture->d_name,".JPG")!=NULL ||
        strstr(lecture->d_name,".jpg")!=NULL || strstr(lecture->d_name,".png")!=NULL)
        {
            en_cours="../data/textures/";
            en_cours+=lecture->d_name;
            addTexture(en_cours);
        }
    }

    dir = opendir("../data/textures/objs");
    while ((lecture = readdir(dir)))
    {
        if(strstr(lecture->d_name,".png")!=NULL)
        {
            en_cours="../data/textures/objs/";
            en_cours+=lecture->d_name;
            addTexture(en_cours);
        }
    }

    dir = opendir("../data/textures/mode");
    while ((lecture = readdir(dir)))
    {
        if(strstr(lecture->d_name,".png")!=NULL)
        {
            en_cours="../data/textures/mode/";
            en_cours+=lecture->d_name;
            addTexture(en_cours);
        }
    }

    dir = opendir("../data/textures/terrain");
    while ((lecture = readdir(dir)))
    {
        if(strstr(lecture->d_name,".png")!=NULL)
        {
            en_cours="../data/textures/terrain/";
            en_cours+=lecture->d_name;
            addTexture(en_cours);
        }
    }

    dir = opendir("../data/textures/signes");
    while ((lecture = readdir(dir)))
    {
        if(strstr(lecture->d_name,".png")!=NULL)
        {
            en_cours="../data/textures/signes/";
            en_cours+=lecture->d_name;
            addTexture(en_cours);
        }
    }
}
void GTexture::reinitialiser()
{
    delAll();
    //m_textures.push_back(new Texture("data/textures/red.jpg"));
    lastBind=NULL;
    //loadAll();
}
void GTexture::addTexture(string c)
{
    bool deja_la=false;
    for(unsigned int i=0;i<m_textures.size();i++)
        if(m_textures[i]!=NULL && c==m_textures[i]->getChemin())
            deja_la=true;

    if(!deja_la)
    {
        m_textures.push_back(new Texture(c));
        m_textures[m_textures.size()-1]->setGtext(this);
    }
}

string GTexture::getSoundGround(string text,int num)
{
    stringstream ss;
    ss << "data/sounds/";
    if(text=="data/textures/herbe.jpg" || text=="data/textures/herbe.JPG" || text=="data/textures/plank.jpg" ||
       text=="data/textures/herbeterre.jpg" || text=="data/textures/terrefonce.jpg" || text=="data/textures/leaf1.jpg"
        || text=="data/textures/carpet_red.jpg" || text=="data/textures/snow.jpg")
        ss << "walkdirt";
    else if(text=="data/textures/floor.jpg" || text=="data/textures/ecorce.jpg" ||
        text=="data/textures/souche.jpg" || text=="data/textures/caisse.jpg" || text=="data/textures/wood2.jpg" ||
        text=="data/textures/wood.jpg" || text=="data/textures/crate.jpg"  ||
        text=="data/textures/ecorce2.jpg" || text=="data/textures/ecorce3.jpg" ||
        text=="data/textures/wood_plank2r.png" || text=="data/textures/wood_plank2.png" ||
        text=="data/textures/wood_plank3r.png" || text=="data/textures/wood_plank3.png")
        ss << "walkwood";
    else if(text=="data/textures/metal.jpg" || text=="data/textures/metal2.jpg" ||
        text=="data/textures/metal2.tga" || text=="data/textures/metal3.jpg" ||
        text=="data/textures/metal4.jpg" || text=="data/textures/grille.png" || text=="data/textures/black_metal.jpg"
         || text=="data/textures/danger2.jpg" || text=="data/textures/danger3.jpg" || text=="data/textures/metal_plate.jpg"
          || text=="data/textures/metal_symbol.png")
        ss << "walkmetal";
    else if(text=="walkwater")
        ss << "walkwater";
    else if(text=="swimwater")
        ss << "swimwater";
    else
        ss << "walkrock";
    ss << num << ".wav";
    return ss.str();
}


Texture* GTexture::getTexture(string c)
{
    for(unsigned int i=0;i<m_textures.size();i++)
        if(c==m_textures[i]->getChemin())
            return m_textures[i];
    return NULL;
}


Texture* GTexture::getTexture(unsigned int index)
{
    if(index<=m_textures.size()-1)
        return m_textures[index];
    return NULL;
}
void GTexture::setLastBind(Texture* t)
{
    lastBind=t;
}
Texture* GTexture::getLastBind()
{
    return lastBind;
}
unsigned int GTexture::getSize()
{
    return m_textures.size();
}

void GTexture::delAll()
{
    for(unsigned int i=0;i<m_textures.size();i++)
    {
        delete m_textures[i];
        m_textures[i]=NULL;
    }
    m_textures.clear();
}



