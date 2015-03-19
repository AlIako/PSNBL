#include "Map.h"
#define MAPSIZE 50
#define WALL_HEIGHT 1000


Map* Map::m_instance = new Map();


Map* Map::getInstance()
{
    return m_instance;
}


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


    Vector3D m_taille=Vector3D(10,10,1);
    if(editor_highestZ!=-1)
    {
        //highest Z
        glColor3ub(0,255,255);
        glTranslated(0,0,editor_highestZ);
        glBegin(GL_QUADS);
        glTexCoord2d(0,1);    glVertex3d(m_taille.X,m_taille.Y,0);
        glTexCoord2d(1,1);    glVertex3d(m_taille.X,-m_taille.Y,0);
        glTexCoord2d(1,0);    glVertex3d(-m_taille.X,-m_taille.Y,0);
        glTexCoord2d(0,0);    glVertex3d(-m_taille.X,m_taille.Y,0);
        glEnd();
        glTranslated(0,0,-editor_highestZ);
    }
    if(editor_nextZ!=-1)
    {
        //next Z
        glColor3ub(0,255,0);
        glTranslated(0,0,editor_nextZ);
        glBegin(GL_QUADS);
        glTexCoord2d(0,1);    glVertex3d(m_taille.X,m_taille.Y,0);
        glTexCoord2d(1,1);    glVertex3d(m_taille.X,-m_taille.Y,0);
        glTexCoord2d(1,0);    glVertex3d(-m_taille.X,-m_taille.Y,0);
        glTexCoord2d(0,0);    glVertex3d(-m_taille.X,m_taille.Y,0);
        glEnd();
        glTranslated(0,0,-editor_nextZ);
    }
    glColor3ub(255,255,255);


}

void Map::update(double functionTime)
{
    ft=functionTime;
    updateMap();

    //objects
    for(unsigned int i=0;i<m_objects.size();i++)
    {
        //update
        m_objects[i]->update(ft);
        //physics, gravity
        applyGravity(m_objects[i]);
        applyPhysics(m_objects[i]);

        //if dead, delete from list
        if(m_objects[i]->getLife()<=0)
        {
            //if a NEXTPHASE bonus was taken, increase lava speed (phase is over)
            if(m_objects[i]->getType()=="bonus")
            {
                if(m_objects[i]->getName()=="nextphase")
                {
                    increaseLavaSpeed();

                    //warning! lava rising
                    Interface::getInstance()->warningLava();
                }
                else if(m_objects[i]->getName()=="startboss")
                {
                    Object* boss=NULL;
                    for(unsigned int i=0;i<m_objects.size();i++)
                    {
                        if(m_objects[i]->getType()=="boss")
                        {
                            boss=m_objects[i];
                            Interface::getInstance()->setTargetBoss(boss);
                        }
                    }
                    if(boss!=NULL)
                        boss->action(0);//start boss

                    Gsounds::getInstance()->addMusic("../data/music/bossbutan.mp3");
                    Gsounds::getInstance()->play("../data/music/bossbutan.mp3");
                }
            }
            else if(m_objects[i]->getType()=="boss")
            {
                Effects::getInstance()->addExplosion(m_objects[i]->getPos(),"bigboom");
                Gsounds::getInstance()->play("../data/sounds/explosion.wav");

                //activate flux
                for(unsigned int i=0;i<m_objects.size();i++)
                {
                    if(m_objects[i]->getType()=="flux" && !m_objects[i]->isActive())
                        m_objects[i]->setActive(true);
                }
                Interface::getInstance()->setTargetBoss(NULL);

                Gsounds::getInstance()->stopMusic();
            }
            else if(m_objects[i]->getType()=="projectile")
            {
                if(distance2V((*playerList)[0]->getPos(),m_objects[i]->getPos())<50)
                {
                    Effects::getInstance()->addExplosion(m_objects[i]->getPos());

                    string sound="../data/sounds/explosion.wav";
                    Gsounds::getInstance()->getSound(sound)->setPos(m_objects[i]->getPos().toLeft());
                    Gsounds::getInstance()->play(sound,1,10,50);
                }
            }
            //delete m_objects[i];
            m_objects.erase(m_objects.begin()+i);
        }
    }
    //players
    for(unsigned int i=0, count=playerList->size();i<count;i++)
        (*playerList)[i]->updateMulti(ft);
    //player
    if(playerList!=NULL && playerList->size()>0)
    {
        (*playerList)[0]->move();


        applyGravity((*playerList)[0]);
        applyPhysics((*playerList)[0]);

        (*playerList)[0]->updateRope();

        (*playerList)[0]->update(ft);

    }

    //lava light
    if(getLava())
        Lighting::getInstance()->setZ("all",getLava()->getPos().Z+getLava()->getSize().Z*2);
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
    Collision::getInstance()->simulatePhysics(o);
}

void Map::ini(string path)
{
    editor_highestZ=-1;
    editor_nextZ=-1;

    //cerr << "ini map"<<endl;

    Collision::getInstance()->setObjects(&m_objects);

    createWalls();

    if(path=="")
    {
        m_phase.ini(&m_objects);
        m_phase.iniMap();
    }
    else
    {
        loadPat(path,10);
        (*playerList)[0]->setPos(Vector3D(0,0,20));
    }


}

void Map::createWalls()
{
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

    Interface::getInstance()->setTargetBoss(NULL);

    Gsounds::getInstance()->stopMusic();
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

    while(0&&curDistance<distanceToReach && !col)
    {
        r.setPos(r.getPos()+target);
        curDistance+=1.0;

        Collision::getInstance()->testCollision(&r,&r);
         Collision::getInstance()->collide(&r);
        if(r.collidedWithHookable())
            col=true;

    }

    if(col)
        ch->setColor(155,0,0);
}


void Map::saveMap(string path)
{
    //�crire map

    char* tempchemin=stringtochar(path);
    ofstream fichier(tempchemin, ios::out | ios::trunc);  // ouverture en �criture avec effacement du fichier ouvert
    delete tempchemin;
    tempchemin=NULL;

    if(fichier)
    {
        string ch="";

        if(editor_highestZ!=-1)
            fichier << "@ highestZ: "<<editor_highestZ<<endl;
        if(editor_nextZ!=-1)
            fichier << "@ nextZ: "<<editor_nextZ<<endl;

        for(unsigned int i=6;i<m_objects.size();i++)
        {
            fichier << m_objects[i]->writeObj();
            fichier << endl;
        }
        fichier.close();
    }
    else
        cerr << "can't open file." << endl;
}

void Map::loadPat(string path,double zOff)
{
    editor_highestZ=-1;
    editor_nextZ=-1;

    char* tempchemin=stringtochar(path);

    std::ifstream in(tempchemin, std::ifstream::ate | std::ifstream::binary);


    ifstream fichier1(tempchemin, ios::in);
    delete tempchemin;
    tempchemin=NULL;


    if(fichier1)
    {
        std::string befor_read="",read_name="",read_name_before="";
        std::string cur_read="";
        int ind=-1;
        int curInt=-1;
        bool addingObject=false;

        while(!fichier1.eof())
        {
            //fichier1 >> cur_read;
            read_name=cur_read.substr(0,cur_read.size()-1);//enleve le ":"

            ind=m_objects.size();
            addingObject=false;

            if(read_name=="block")
            {
                m_objects.push_back(new Block());
                addingObject=true;
            }
            else if(read_name=="bonus")
            {
                m_objects.push_back(new Bonus());
                addingObject=true;
            }
            else if(read_name=="flux")
            {
                m_objects.push_back(new Flux());
                addingObject=true;
            }
            else if(read_name=="boss")
            {
                m_objects.push_back(new BossButan());
                addingObject=true;
            }
            else if(read_name=="highestZ")
            {
                fichier1 >> curInt;
                editor_highestZ=zOff+curInt;
            }
            else if(read_name=="nextZ")
            {
                fichier1 >> curInt;
                editor_nextZ=zOff+curInt;
            }

            if(addingObject)
            {
                m_objects[ind]->readObj(&fichier1);
                m_objects[ind]->ini();
                m_objects[ind]->setPos(m_objects[ind]->getPos()+Vector3D(0,0,zOff));

                //actually we dont want that one (walls)
                if(m_objects[ind]->getSize().Z>=1000)
                {
                    delete m_objects[ind];
                    m_objects.pop_back();
                }
            }





            fichier1 >> cur_read;
            befor_read=cur_read;
            read_name_before=befor_read.substr(0,befor_read.size()-1);//enleve le ":"


        }

        fichier1.close();
    }
    else
        cerr << "can't open file (pattern file)" << endl;
}


void Map::deleteLastObj()
{
    if(m_objects.size()>0)
    {
        delete m_objects[m_objects.size()-1];
        m_objects.pop_back();
    }
}


void Map::translateAll(Vector3D t)
{
    for(unsigned int i=0;i<m_objects.size();i++)
    {
        m_objects[i]->setPos(m_objects[i]->getPos()+t);
    }
}

