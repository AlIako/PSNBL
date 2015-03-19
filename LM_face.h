#ifndef CFACE_H
#define CFACE_H
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include "Vector3D.h"

class CFace
{
    public:
    CFace();
    ~CFace();
    void createFace(Vector3D v1, Vector3D v2, Vector3D v3, Vector3D vt1, Vector3D vt2, Vector3D vt3, Vector3D vn1,
    Vector3D vn2, Vector3D vn3);
    void drawFace();

    private:
    bool creer;
    std::vector<Vector3D> m_vertices;
    std::vector<Vector3D> m_vertexes;
    std::vector<Vector3D> m_normals;
};

#endif
