#ifndef GTEXTURES_H_INCLUDED
#define GTEXTURES_H_INCLUDED
#include <vector>
#include <sstream>
#include <dirent.h>
class GTexture;
#include "Texture.h"

using namespace std;


class GTexture
{
    public:
    GTexture();

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


    private:

    std::vector < Texture* > m_textures;
    Texture* lastBind;
};

//extern GTexture* gtex;
/*

class GetGT
{
    public:
    GetGT()
    {
        gt=NULL;
    }
    GTexture* get()
    {
        if(gt==NULL)
            gt=new GTexture();

        return gt;
    }
    private:
    GTexture* gt;
};
extern GetGT getgt=GetGT();*/

#endif // GTEXTURES_H_INCLUDED
