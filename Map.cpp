#include "Map.h"
#define MAPSIZE 50
#define WALL_HEIGHT 1000


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
            //if a REZ bonus was taken, increase lava speed (phase is over)
            if(m_objects[i]->getType()=="bonus" && m_objects[i]->getName()=="rez")
            {
                increaseLavaSpeed();
            }
            //delete m_objects[i];
            m_objects.erase(m_objects.begin()+i);
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
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(2,MAPSIZE,2));
    m_objects[ind]->setSize(Vector3D(MAPSIZE,2,WALL_HEIGHT));

    ind=m_objects.size();
    m_objects.push_back(new Wall());
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(MAPSIZE,2,2));
    m_objects[ind]->setSize(Vector3D(2,MAPSIZE,WALL_HEIGHT));

    ind=m_objects.size();
    m_objects.push_back(new Wall());
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(-MAPSIZE,2,2));
    m_objects[ind]->setSize(Vector3D(2,MAPSIZE,WALL_HEIGHT));

    ind=m_objects.size();
    m_objects.push_back(new Wall());
    m_objects[ind]->ini();
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(2,-MAPSIZE,2));
    m_objects[ind]->setSize(Vector3D(MAPSIZE,2,WALL_HEIGHT));

    //lava
    ind=m_objects.size();
    m_objects.push_back(new Lava());
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(0,0,4));
    m_objects[ind]->setSize(Vector3D(MAPSIZE,MAPSIZE,2));

    //floor
    ind=m_objects.size();
    m_objects.push_back(new Block());
    m_objects[ind]->ini();
    m_objects[ind]->setPos(Vector3D(0,0,2));
    m_objects[ind]->setSize(Vector3D(MAPSIZE,MAPSIZE,2));


    m_phase.ini(&m_objects);
    m_phase.iniMap();


}

void Map::increaseLavaSpeed()
{
    Object* lava=getLava();
    if(lava) lava->setSpeed(2);
}

void Map::setLavaLevel(double z)
{
    cerr<<"adjusting laval evel"<<endl;

    Object* lava=getLava();
    if(lava) lava->setSize(Vector3D(lava->getSize().X,lava->getSize().Y,z));
}
double Map::getLavaLevel()
{
    double lvl=-1;

    Object* lava=getLava();
    if(lava) lvl=lava->getSize().Z;

    return lvl;
}

Object* Map::getLava()
{
    for(unsigned int i=0,count=m_objects.size();i<count;i++)
    {
        if(m_objects[i]->getType()=="lava")
            return m_objects[i];
    }
    return NULL;
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


void Map::simulateRopeForCrosshair(Player* p, Vector3D target, Crosshair* ch)
{
    ch->setColor(155,155,155);

    Rope r=Rope();
    r.ini(p->getPos(),target);
    r.setFT(ft);
    r.setPos(p->getPos());

    double distanceToReach=50;
    double curDistance=0;

    bool col=false;
    Collision c;
    c.setObjects(&m_objects);

    while(curDistance<distanceToReach && !col)
    {
        r.setPos(r.getPos()+target);
        curDistance+=1.0;

        c.testCollision(&r,&r);
        c.collide(&r);
        if(r.collidedWithHookable())
            col=true;

    }

    if(col)
        ch->setColor(155,0,0);
}





