#include "Map.h"
#define MAPSIZE 50
#define WALL_HEIGHT 400


Map::Map()
{
    playerList=NULL;
}

void Map::draw()
{
    for(unsigned int i = 0;i<m_objects.size();i++)
    {
        if(!m_objects[i]->getTransparency())
            m_objects[i]->draw();
    }
    for(unsigned int i = 0;i<m_objects.size();i++)
    {
        if(m_objects[i]->getTransparency())
            m_objects[i]->draw();
    }
}

void Map::update(double functionTime)
{
    ft=functionTime;

    //objects
    for(unsigned int i=0, count=m_objects.size();i<count;i++)
    {
        //update
        m_objects[i]->update(ft);
        //physics, gravity
        applyGravity(m_objects[i]);
        applyPhysics(m_objects[i]);
        //if dead, delete from list
        if(m_objects[i]->getLife()<=0)
        {
            delete m_objects[i];
            for(unsigned int j=i;j<count-1;j++)
                m_objects[j]=m_objects[j+1];
            m_objects.pop_back();
        }
    }
    //players
    for(unsigned int i=0, count=playerList->size();i<count;i++)
    {
        (*playerList)[i]->update(ft);
        (*playerList)[i]->move();
    }
    //player
    if(playerList!=NULL && playerList->size()>0)
    {
        applyGravity((*playerList)[0]);
        applyPhysics((*playerList)[0]);
    }
}

Rope* Map::createRope(Vector3D start, Vector3D target)
{
    Rope* rope=new Rope();
    rope->gtext=gtext;
    rope->ini(start,target);

    m_objects.push_back(rope);

    return rope;
}


void Map::applyGravity(Object* o)
{
    o->applyGravity();
}

void Map::applyPhysics(Object* o)
{
    //simulate physics
    Collision c;
    c.setObjects(&m_objects);
    c.simulatePhysics(o);
}

void Map::ini()
{
    //cerr << "ini map"<<endl;

    //walls
    unsigned int ind=0;
    m_objects.push_back(new Wall());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(2,MAPSIZE,2));
    m_objects[ind]->setSize(Vector3D(MAPSIZE,2,WALL_HEIGHT));

    ind=m_objects.size();
    m_objects.push_back(new Wall());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(MAPSIZE,2,2));
    m_objects[ind]->setSize(Vector3D(2,MAPSIZE,WALL_HEIGHT));

    ind=m_objects.size();
    m_objects.push_back(new Wall());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(-MAPSIZE,2,2));
    m_objects[ind]->setSize(Vector3D(2,MAPSIZE,WALL_HEIGHT));

    ind=m_objects.size();
    m_objects.push_back(new Wall());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(2,-MAPSIZE,2));
    m_objects[ind]->setSize(Vector3D(MAPSIZE,2,WALL_HEIGHT));

    //lava
    ind=m_objects.size();
    m_objects.push_back(new Lava());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(0,0,4));
    m_objects[ind]->setSize(Vector3D(MAPSIZE,MAPSIZE,2));

    //floor
    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(0,0,2));
    m_objects[ind]->setSize(Vector3D(MAPSIZE,MAPSIZE,2));

    //blocks
    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(10,10,4));
    m_objects[ind]->setSize(Vector3D(4,4,4));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(10,15,8));
    m_objects[ind]->setSize(Vector3D(2,2,4));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(2,-MAPSIZE,2));
    m_objects[ind]->setSize(Vector3D(MAPSIZE,10,8));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(MAPSIZE,2,18));
    m_objects[ind]->setSize(Vector3D(10,MAPSIZE,4));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(-MAPSIZE/1.5,-MAPSIZE/1.5,4));
    m_objects[ind]->setSize(Vector3D(10,10,4));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(-10,-30,30));
    m_objects[ind]->setSize(Vector3D(8,8,12));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(10,0,40));
    m_objects[ind]->setSize(Vector3D(8,8,12));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(-10,30,60));
    m_objects[ind]->setSize(Vector3D(8,8,12));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(-10,-30,80));
    m_objects[ind]->setSize(Vector3D(8,8,12));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(10,0,100));
    m_objects[ind]->setSize(Vector3D(8,8,12));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(-10,30,120));
    m_objects[ind]->setSize(Vector3D(8,8,12));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(-10,-30,140));
    m_objects[ind]->setSize(Vector3D(8,8,12));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(10,0,160));
    m_objects[ind]->setSize(Vector3D(8,8,12));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(-10,30,180));
    m_objects[ind]->setSize(Vector3D(8,8,12));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(-10,-30,200));
    m_objects[ind]->setSize(Vector3D(8,8,12));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(10,0,220));
    m_objects[ind]->setSize(Vector3D(8,8,12));

    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->gtext=gtext;
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(-10,30,240));
    m_objects[ind]->setSize(Vector3D(8,8,12));

}












