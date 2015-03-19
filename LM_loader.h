#ifndef COBJLOADER_H
#define COBJLOADER_H
#include "Gtexture.h"
#include "LM_face.h"

class CObjLoader
{
    public:
    CObjLoader();
    ~CObjLoader();
    void loadMesh(char *fileName, std::vector<CFace> *m_faces);
    Texture* getTexture(char *fileName);

    private:
    void count(char *fileName);
    void createFaces(char *fileName, std::vector<CFace> *m_faces);
    unsigned int m_nbVertices, m_nbNormals, m_nbVertexes, m_nbFaces;
    std::vector<Vector3D> m_vertices;
    std::vector<Vector3D> m_vertexes;
    std::vector<Vector3D> m_normals;
};

#endif
