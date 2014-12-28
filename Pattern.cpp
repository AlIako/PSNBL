#include "Pattern.h"






Pattern::Pattern()
{
    video=NULL;
    online=NULL;
    m_lavaspeed=0;
    m_name="pattern";

    m_fogdistancestart=100;
    m_fogdistanceend=300;
    m_fogr=0.0f;
    m_fogg=0.0f;
    m_fogb=0.0f;
}


void Pattern::start()
{
    m_lava->setSpeed(m_lavaspeed);
    if(video!=NULL)
        video->getFog()->setTarget(m_fogdistancestart,m_fogdistanceend,m_fogr,m_fogg,m_fogb);
}

void Pattern::update(double functionTime)
{
    //check for pattern end
    //cerr<<"checking if "<<  m_lava->getPos().Z+m_lava->getSize().Z<<" >= "<<m_highestZ <<endl;
    if(m_lava->getPos().Z+m_lava->getSize().Z*2>=m_highestZ)
    {
        cerr<<"pattern "<<m_name<<" finished!"<<endl;
        m_finished=true;
    }
}

void Pattern::calculHighestZ()
{
    m_highestZ=0;
    for(unsigned int i=0,count=m_objects->size();i<count;i++)
    {
        if((*m_objects)[i]->getType()!="wall" && (*m_objects)[i]->getType()!="lava")
        {
            if((*m_objects)[i]->getPos().Z+(*m_objects)[i]->getSize().Z>m_highestZ)
                m_highestZ=(*m_objects)[i]->getPos().Z+(*m_objects)[i]->getSize().Z;
        }
    }
}

void Pattern::ini(double startZ, std::vector<Object*>* objects)
{
    m_startZ=startZ;
    m_objects=objects;


    cerr<<"ini pattern "<<m_name<<". start Z is: "<<startZ <<endl;
    m_finished=false;

    //find walls and lava
    m_lava=NULL;
    m_walls.clear();
    for(unsigned int i=0,count=objects->size();i<count;i++)
    {
        if((*objects)[i]->getType()=="wall")
            m_walls.push_back((*objects)[i]);
        else if((*objects)[i]->getType()=="lava")
            m_lava=(*objects)[i];
    }

    calculHighestZ();


    m_lavaspeed=0.1;
    m_fogdistancestart=100;
    m_fogdistanceend=300;
    m_fogr=0.0f;
    m_fogg=0.0f;
    m_fogb=0.0f;
}


int Pattern::getPID()
{
    if(m_name=="still")
        return 1;
    if(m_name=="PatBigBlocks")
        return 2;
    if(m_name=="PatBeams")
        return 3;
    if(m_name=="PatMidBlocks")
        return 4;
    return 0;
}






