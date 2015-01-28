#include "Pattern.h"






Pattern::Pattern()
{
    video=NULL;
    m_name="pattern";
}


void Pattern::start()
{
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
                m_highestZ=(*m_objects)[i]->getPos().Z+(*m_objects)[i]->getSize().Z*2;
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
    if(m_name=="PatEndPhase")
        return 5;
    if(m_name=="PatLetsGo")
        return 6;
    if(m_name=="PatHookAround")
        return 7;
    return 0;
}






