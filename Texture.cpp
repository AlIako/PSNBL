#include "Texture.h"


Texture::Texture(string chemin)
{
    m_type="stone";
    if(chemin!="")
        load(chemin);
}

void Texture::load(string c)
{
    int tempsPrecedent=SDL_GetTicks();
    m_chemin=c;

    char* tempString=stringtochar(c);
    m_id=loadTexture(tempString);
    delete tempString;

    choseType(c);
    if(m_id!=0)
        cerr << "Texture " << c << "(" << SDL_GetTicks()-tempsPrecedent << "ms)." << endl;
    else
        cerr << "Echec du chargement de la texture " << c << " !" << endl;
}
void Texture::choseType(string c)
{
    if(c=="data/textures/herbe.JPG")
        m_type="grass";
    else if(c=="data/textures/rock.JPG")
        m_type="stone";
    else if(c=="data/textures/plank.JPG")
        m_type="dirt";
}
void Texture::bind(bool force)
{
    if((gtext->getLastBind()!=this || gtext->getLastBind()==NULL || force))
    {
        glBindTexture(GL_TEXTURE_2D,m_id);
        gtext->setLastBind(this);
    }
    //glBindTexture(GL_TEXTURE_2D,m_id);
}

string Texture::getChemin()
{
    return m_chemin;
}

void Texture::cleanBorders()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);

    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
}
