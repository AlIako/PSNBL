#include "LM_face.h"

using namespace std;

CFace::CFace()
{
    creer=false;
}

void CFace::createFace(Vector3D v1, Vector3D v2, Vector3D v3,
Vector3D vt1, Vector3D vt2, Vector3D vt3,
Vector3D vn1, Vector3D vn2, Vector3D vn3)
{
    m_vertexes.clear();
    m_vertices.clear();
    m_normals.clear();

    m_vertices.resize(3);
    m_vertices[0] = v1;
    m_vertices[1] = v2;
    m_vertices[2] = v3;

    m_vertexes.resize(3);
    m_vertexes[0] = vt1;
    m_vertexes[1] = vt2;
    m_vertexes[2] = vt3;

    m_normals.resize(3);
    m_normals[0] = vn1;
    m_normals[1] = vn2;
    m_normals[2] = vn3;
    creer=true;
}

void CFace::drawFace()
{
    if(creer)
    {
        glNormal3d(m_normals[0].X,m_normals[0].Y,m_normals[0].Z);
        glTexCoord2d(m_vertexes[0].X,m_vertexes[0].Y); glVertex3d(m_vertices[0].X,m_vertices[0].Y,m_vertices[0].Z);
        glNormal3d(m_normals[1].X,m_normals[1].Y,m_normals[1].Z);
        glTexCoord2d(m_vertexes[1].X,m_vertexes[1].Y); glVertex3d(m_vertices[1].X,m_vertices[1].Y,m_vertices[1].Z);
        glNormal3d(m_normals[2].X,m_normals[2].Y,m_normals[2].Z);
        glTexCoord2d(m_vertexes[2].X,m_vertexes[2].Y); glVertex3d(m_vertices[2].X,m_vertices[2].Y,m_vertices[2].Z);
    }
}

CFace::~CFace()
{
    m_vertexes.clear();
    m_vertices.clear();
    m_normals.clear();
}
