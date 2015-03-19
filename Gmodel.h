#ifndef GMODEL_H_INCLUDED
#define GMODEL_H_INCLUDED
#include <string>
#include <vector>
#include "utilFunctions.h"
#include "Sprite.h"
#include "LM_mesh.h"
#include "LoaderMD2.h"
#include "GTexture.h"

class Gmodel
{
    public:
    static Gmodel* getInstance();

    void reini();
    void drawSculpture(std::string sculpt);
    void addMesh(std::string chemin);
    void addMD2(std::string chemin);
    void addSprite(std::string chemin);
    Sprite* getSprite(std::string nom);
    CMesh* getMesh(std::string nom);
    md2_model_t* getMD2(std::string nom);
    void delAll();

    private:
    Gmodel();
    static Gmodel* m_instance;

    CObjLoader loader;
    std::vector<CMesh*> meshes;
    std::vector<md2_model_t*> md2models;
    std::vector<Sprite*> sprites;

    //rocket
    Texture* m_texture1;
    Texture* m_texture2;
    Texture* m_texture3;
    Texture* m_texture4;
    Texture* m_texture5;
};


#endif // GMODEL_H_INCLUDED
