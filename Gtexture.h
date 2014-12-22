#ifndef GTEXTURES_H_INCLUDED
#define GTEXTURES_H_INCLUDED
#include <vector>
#include <sstream>
#include <dirent.h>
class Gtexture;
#include "Texture.h"

using namespace std;

class Gtexture
{
    public:
    Gtexture();

    void loadAll();
    void reinitialiser();

    void addTexture(string c);


    string getSoundGround(string text,int num);

    Texture* getTexture(string c);
    Texture* getTexture(unsigned int index);

    void setLastBind(Texture* t);
    Texture* getLastBind();

    unsigned int getSize();

    void delAll();

    std::vector < Texture* > m_textures;
    Texture* lastBind;


    private:
};

#endif // GTEXTURES_H_INCLUDED
