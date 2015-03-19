#include <fstream>
#include <iostream>
#include <string>
#include "LM_loader.h"
#include "utilFunctions.h"
#include "sdlglutils.h"

using namespace std;

CObjLoader::CObjLoader()
{
    m_nbVertices=0;
    m_nbVertexes=0;
    m_nbNormals=0;
    m_nbFaces=0;
    m_vertices.clear();
    m_vertexes.clear();
    m_normals.clear();
}

void CObjLoader::loadMesh(char *fileName, std::vector<CFace> *m_faces)
{
    //compte nombre vertices, vertexes, normales, faces
    count(fileName);

    //redimensionne les tableaux dynamiques
    m_vertices.resize(m_nbVertices);
    m_vertexes.resize(m_nbVertexes);
    m_normals.resize(m_nbNormals);
    m_faces->resize(m_nbFaces);

    //puis créé les faces
    createFaces(fileName,m_faces);
}

Texture* CObjLoader::getTexture(char *fileName)
{
    if(m_nbVertexes>0)//si ya une texture
    {
        std::string mtlNameS=fileName;
        mtlNameS=mtlNameS.substr(0,mtlNameS.size()-4);//enleve le .obj du nom
        mtlNameS+=".mtl";
        char* mtlName=stringtochar(mtlNameS);
        Texture* texture;
        char* chemin_texture;
        std::string chaineALire="";

        ifstream file(mtlName, ios::in);
        if(file)
        {
            while(!file.eof())
            {
                file >> chaineALire;
                if(chaineALire.find(".tga")!=string::npos
                || chaineALire.find(".JPEG")!=string::npos
                || chaineALire.find(".PNG")!=string::npos
                || chaineALire.find(".png")!=string::npos
                || chaineALire.find(".JPG")!=string::npos
                || chaineALire.find(".jpg")!=string::npos
                || chaineALire.find(".pcx")!=string::npos
                || chaineALire.find(".bmp")!=string::npos
                || chaineALire.find(".dds")!=string::npos)
                {
                    chemin_texture=stringtochar("../data/mesh/"+chaineALire);
                }
            }
            file.close();
        }
        else
            cerr << "can't not open file (model) : " << mtlName << endl;

        texture=NULL;
        GTexture::getInstance()->addTexture(chemin_texture);
        texture=GTexture::getInstance()->getTexture(chemin_texture);

        delete chemin_texture;
        delete mtlName;
        chemin_texture=NULL;
        mtlName=NULL;

        return texture;
    }
    return 0;
}

void CObjLoader::count(char *fileName)
{
    m_vertices.clear();
    m_vertexes.clear();
    m_normals.clear();
    m_nbVertices=0;
    m_nbVertexes=0;
    m_nbNormals=0;
    m_nbFaces=0;

    ifstream file(fileName, ios::in);
    if(file)
    {
        char charactere, lastChar;
        while(!file.eof())
        {
            lastChar = charactere;
            file.get(charactere);
            if(lastChar == 'v' && charactere == ' ')
            m_nbVertices++;
            else if(lastChar == 'v' && charactere == 't')
            m_nbVertexes++;
            else if(lastChar == 'v' && charactere == 'n')
            m_nbNormals++;
            else if(lastChar == 'f' && charactere == ' ')
            m_nbFaces++;
        }
        file.close();
    }
    else
        cerr << "could not open file : " << fileName << endl;
}

void CObjLoader::createFaces(char *fileName, std::vector<CFace> *m_faces)
{
    ifstream file(fileName, ios::in);
    if(file)
    {
        char charactere, lastChar;
        unsigned int v=0, vt=0, vn=0, f=0;
        float x=0, y=0, z=0;
        unsigned int v1=0, v2=0, v3=0, vt1=0, vt2=0, vt3=0, vn1=0, vn2=0, vn3=0;

        while(!file.eof())
        {
            lastChar = charactere;
            file.get(charactere);

            if(lastChar=='v' && charactere==' ')//vertice
            {
                //on attribue les coordonnées du vertice courant au v-ème vertice de notre liste
                file >> x >> y >> z;
                if(v<m_nbVertices)
                    m_vertices[v]=Vector3D(x,y,z);
                v++;
            }
            else if(lastChar=='v' && charactere=='t')//vertex
            {
                //on attribue les coordonnées du vertex courant au vt-ème vertex de notre liste
                file >> x >> y;
                if(vt<m_nbVertexes)
                {
                    m_vertexes[vt].X=x;
                    m_vertexes[vt].Y=y;
                    m_vertexes[vt].Z=0;
                }
                vt++;
            }
            else if(lastChar=='v' && charactere=='n')//normale
            {
                //on attribue les coordonnées de la normale courante à la vt-ème normale de notre liste
                file >> x >> y >> z;
                Vector3D normal;
                normal=Vector3D(x,y,z);
                if(vn<m_nbNormals)
                    m_normals[vn]=normal;
                vn++;
            }
            //On créer les faces sachant qu'il y a TOUJOURS des vertices
            else if(lastChar=='f' && charactere==' ')//face
            {
                //si il y a des coordonnées de textures ET de normales
                //Le fichier est sous cette forme || f 4/3/2 5/4/1 6/2/3
                if(m_nbVertexes>0 && m_nbNormals>0)
                {
                    //Vertice1
                    file >> v1;
                    file.get(charactere);
                    file >> vt1;
                    file.get(charactere);
                    file >> vn1;
                    //Vertice2
                    file >> v2;
                    file.get(charactere);
                    file >> vt2;
                    file.get(charactere);
                    file >> vn2;
                    //Vertice3
                    file >> v3;
                    file.get(charactere);
                    file >> vt3;
                    file.get(charactere);
                    file >> vn3;
                    //je me place aux lignes vt1, vt2, vt3 et je prends les valeurs vt1 et vt2...

                    if(v1<=m_vertices.size() && v2<=m_vertices.size() && v3<=m_vertices.size() &&
                    vt1<=m_vertexes.size() && vt2<=m_vertexes.size() && vt3<=m_vertexes.size() &&
                    vn1<=m_normals.size() && vn2<=m_normals.size() && vn3<=m_normals.size() &&
                    v1>0 && v2>0 && v3>0 && vt1>0 && vt2>0 && vt3>0 &&
                    vn1>0 && vn2>0 && vn3>0 && f<m_faces->size())
                    {
                        /*cerr << m_vertices[v1-1].X << "," << m_vertices[v1-1].Y << "," << m_vertices[v1-1].Z << " " <<
                        m_vertices[v2-1].X << "," << m_vertices[v2-1].Y << "," << m_vertices[v2-1].Z << " " <<
                        m_vertices[v3-1].X << "," << m_vertices[v3-1].Y << "," << m_vertices[v3-1].Z << " " <<
                        m_vertexes[vt1-1].X << "," << m_vertexes[vt1-1].Y << "," << m_vertexes[vt1-1].Z << " " <<
                        m_vertexes[vt2-1].X << "," << m_vertexes[vt2-1].Y << "," << m_vertexes[vt2-1].Z << " " <<
                        m_vertexes[vt3-1].X << "," << m_vertexes[vt3-1].Y << "," << m_vertexes[vt3-1].Z << " " <<
                        m_normals[vn1-1].X << "," << m_normals[vn1-1].Y << "," << m_normals[vn1-1].Z << " " <<
                        m_normals[vn2-1].X << "," << m_normals[vn2-1].Y << "," << m_normals[vn2-1].Z << " " <<
                        m_normals[vn3-1].X << "," << m_normals[vn3-1].Y << "," << m_normals[vn3-1].Z << " " <<
                        endl;*/

                        (*m_faces)[f].createFace(m_vertices[v1-1], m_vertices[v2-1], m_vertices[v3-1],
                        m_vertexes[vt1-1], m_vertexes[vt2-1], m_vertexes[vt3-1],
                        m_normals[vn1-1], m_normals[vn2-1], m_normals[vn3-1]);
                    }
                    f++;
                }
                //Si il y a des textures mais PAS de normales (f 3/4 3/2 4/5)
                else if(m_nbVertexes>0 && m_nbNormals==0)
                {
                }
                //si il n'y a pas de textures mais qu'il y a des normales (f 4//3 2//5 1//2)
                else if(m_nbVertexes==0 && m_nbNormals>0)
                {
                    //Vertice1
                    file >> v1;
                    vt1=0;
                    file.get(charactere);
                    file.get(charactere);
                    file >> vn1;
                    //Vertice2
                    file >> v2;
                    vt2=0;
                    file.get(charactere);
                    file.get(charactere);
                    file >> vn2;
                    //Vertice3
                    file >> v3;
                    vt3=0;
                    file.get(charactere);
                    file.get(charactere);
                    file >> vn3;

                    if(v1<m_vertices.size() && v2<m_vertices.size() && v3<m_vertices.size() &&
                    vt1<m_vertexes.size() && vt2<m_vertexes.size() && vt3<m_vertexes.size() &&
                    vn1<m_normals.size() && vn2<m_normals.size() && vn3<m_normals.size() && f<m_faces->size())
                    {
                        (*m_faces)[f].createFace(m_vertices[v1-1], m_vertices[v2-1], m_vertices[v3-1],
                        m_vertexes[vt1-1], m_vertexes[vt2-1], m_vertexes[vt3-1],
                        m_normals[vn1-1], m_normals[vn2-1], m_normals[vn3-1]);
                    }

                    f++;
                }
                //Si il n'y a que des points (f 4 3 5)
                else
                {
                    file >> v1 >> v2 >> v3;
                    f++;
                }
            }
        }
        file.close();
    }
    else
        cerr << "could not open file : " << fileName << endl;
}

CObjLoader::~CObjLoader()
{
    m_vertices.clear();
    m_vertexes.clear();
    m_normals.clear();
}
