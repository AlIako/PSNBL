#ifndef CMESH_H
#define CMESH_H
#include <string>
#include "LM_loader.h"
#include "LM_face.h"

class CMesh
{
    public:
    CMesh();
    ~CMesh();
    void loadMesh(char *fileName, CObjLoader *loader);
    void draw();
    void drawNoTexture();
    void bindText();
    std::string getRepertoire();

    private:
    bool loaded;
    std::vector<CFace> m_faces;
    Texture* m_texture;
    std::string m_repertoire;
};

#endif
