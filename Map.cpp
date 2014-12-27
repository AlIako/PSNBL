#include "Map.h"
#define MAPSIZE 50
#define WALL_HEIGHT 1000


Map::Map()
{
    playerList=NULL;
    online=NULL;
    video=NULL;
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
    updateMap();

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
            //delete m_objects[i];
            for(unsigned int j=i;j<count-1;j++)
                m_objects[j]=m_objects[j+1];
            m_objects.pop_back();
        }
    }
    //players
    /*for(unsigned int i=0, count=playerList->size();i<count;i++)
    {
        (*playerList)[i]->update(ft);
        (*playerList)[i]->move();
    }*/
    //player
    if(playerList!=NULL && playerList->size()>0)
    {
        (*playerList)[0]->update(ft);
        (*playerList)[0]->move();

        applyGravity((*playerList)[0]);
        applyPhysics((*playerList)[0]);
    }
}

void Map::updateMap()
{
    m_phase.update(ft);
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


    m_phase.m_incontrol=m_incontrol;
    m_phase.video=video;
    m_phase.online=online;
    m_phase.gtext=gtext;
    m_phase.ini(&m_objects);
    m_phase.iniMap();


}


void Map::addPatternToQueue(int p)
{
    m_phase.addPatternToQueue(p);
}

void Map::setLavaLevel(double z)
{
    cerr<<"adjusting laval evel"<<endl;
    for(unsigned int i=0,count=m_objects.size();i<count;i++)
    {
        if(m_objects[i]->getType()=="lava")
            m_objects[i]->setSize(Vector3D(m_objects[i]->getSize().X,m_objects[i]->getSize().Y,z));
    }
}
double Map::getLavaLevel()
{
    double lvl=-1;
    for(unsigned int i=0,count=m_objects.size();i<count;i++)
    {
        if(m_objects[i]->getType()=="lava")
            lvl=m_objects[i]->getSize().Z;
    }

    return lvl;
}


void Map::restart()
{
    erase();
    ini();

    (*playerList)[0]->resurrect();
}


void Map::erase()
{
    m_phase.erase();

    for(unsigned int i=0,count=m_objects.size();i<count;i++)
        delete m_objects[i];
    m_objects.clear();
}







