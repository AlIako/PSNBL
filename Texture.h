#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include <iostream>
#include "sdlglutils.h"
#include "utilFunctions.h"
class Texture;
#include "Gtexture.h"

using namespace std;

class Texture
{
    public:
    Texture(string chemin="");
    void load(string c);
    void choseType(string c);
    void bind(bool force=false);
    string getChemin();
    void cleanBorders();
    void setGtext(Gtexture* gt) {gtext=gt;}

    private:
    Gtexture *gtext;
    string m_type;
    string m_chemin;
    GLuint m_id;

};
#endif // TEXTURE_H_INCLUDED
