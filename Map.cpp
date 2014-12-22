#include "Map.h"
#define MAPSIZE 50
#define WALL_HEIGHT 400


Map::Map()
{

}




void Map::ini()
{
    //cerr << "ini map"<<endl;

    //walls
    unsigned int ind=0;
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(2,MAPSIZE,WALL_HEIGHT));
    m_objects[ind]->setSize(Vector3D(MAPSIZE,2,WALL_HEIGHT));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(MAPSIZE,2,WALL_HEIGHT));
    m_objects[ind]->setSize(Vector3D(2,MAPSIZE,WALL_HEIGHT));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(-MAPSIZE,2,WALL_HEIGHT));
    m_objects[ind]->setSize(Vector3D(2,-MAPSIZE,WALL_HEIGHT));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(2,-MAPSIZE,WALL_HEIGHT));
    m_objects[ind]->setSize(Vector3D(-MAPSIZE,2,WALL_HEIGHT));

    //floor
    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(0,0,2));
    m_objects[ind]->setSize(Vector3D(MAPSIZE,MAPSIZE,2));
}



void Map::draw()
{
    for(unsigned int i = 0;i<m_objects.size();i++)
    {
        m_objects[i]->draw();
    }
}



