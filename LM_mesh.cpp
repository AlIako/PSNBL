#include "LM_mesh.h"
#include <iostream>
#include "utilFunctions.h"

using namespace std;

CMesh::CMesh()
{
    loaded=false;
    m_texture=0;
    m_repertoire="";
    m_faces.clear();
}

void CMesh::loadMesh(char *fileName, CObjLoader *loader)
{
    if(!loaded)
    {
        int tempsPrecedent=SDL_GetTicks();
        m_repertoire=fileName;

        loader->loadMesh(fileName,&m_faces);

        m_texture = loader->getTexture(fileName);
        cerr << "Mesh " << m_repertoire << "," << m_faces.size() << " faces(" <<
        SDL_GetTicks()-tempsPrecedent << "ms)." <<endl;
    }
    if(m_faces.size()>0)
        loaded=true;
}

void CMesh::draw()
{
    if(loaded)
    {
        m_texture->bind();
        drawNoTexture();
    }
}

void CMesh::drawNoTexture()
{
    if(loaded)
    {
        glBegin(GL_TRIANGLES);
        if(m_faces.size()>0)
            for(unsigned int i=0; i<m_faces.size(); i++)
            {
                //cerr<<"drawing face "<<i<<endl;
                m_faces[i].drawFace();
            }
        glEnd();
    }
}

void CMesh::bindText()
{
    if(m_texture!=NULL)
        m_texture->bind();
}

std::string CMesh::getRepertoire()
{
    return m_repertoire;
}


CMesh::~CMesh()
{
    m_faces.clear();
}
