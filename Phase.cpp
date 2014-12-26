#include "Phase.h"





Phase::Phase()
{
    m_fogdistance=100;
    m_name="still";

    highestZ=-100;

}




void Phase::ini(std::vector<Object*>* objects)
{
    m_patternQueue.clear();

    cerr<<"ini phase "<<m_name<<endl;
    //find walls and lava
    m_objects=objects;

    m_lava=NULL;
    m_walls.clear();
    for(unsigned int i=0,count=objects->size();i<count;i++)
    {
        if((*objects)[i]->getType()=="wall")
            m_walls.push_back((*objects)[i]);
        else if((*objects)[i]->getType()=="lava")
            m_lava=(*objects)[i];
    }
    if(m_lava==NULL)
        cerr<<"WARNING! lava not found"<<endl;
    highestZ=m_lava->getPos().Z+m_lava->getSize().Z;

}


void Phase::nextPattern()
{
    //delete first pattern from queue
    delete m_patternQueue[0];
    for(unsigned int i=0, count=m_patternQueue.size()-1;i<count;i++)
        m_patternQueue[i]=m_patternQueue[i+1];
    m_patternQueue.pop_back();

    //take first pattern from queue
    m_pattern=m_patternQueue[0];

    //apply pattern
    m_pattern->start();

    //add pattern to queue
    addPatternToQueue();
}

void Phase::addPatternToQueue()
{
    int randomizer=myIntRand(0,100);
    if(m_name=="still")
    {
        //first pattern is still
        if(m_patternQueue.size()==0)
            m_patternQueue.push_back(new PatStill());
        else
        {
            //next pattern are random
            if(randomizer>50)
                m_patternQueue.push_back(new PatStill());
            else if(randomizer>0)
                m_patternQueue.push_back(new PatBigBlocks());
        }
    }
    //ini those new patterns but dont start them yet
    if(m_patternQueue.size()>0)
    {
        m_patternQueue[m_patternQueue.size()-1]->gtext=gtext;
        m_patternQueue[m_patternQueue.size()-1]->ini(highestZ,m_objects);
        highestZ=m_patternQueue[m_patternQueue.size()-1]->getHighestZ();
    }
}

void Phase::iniMap()
{
    cerr<<"ini mapphase "<<m_name<<endl;

    m_patternQueue.clear();
    //add pattern to queue
    addPatternToQueue();
    addPatternToQueue();
    /*addPatternToQueue();
    addPatternToQueue();
    addPatternToQueue();*/

    //nextPattern();
    m_pattern=m_patternQueue[0];
    m_pattern->start();
}


void Phase::update(double functionTime)
{
    m_pattern->update(functionTime);
    if(m_pattern->finished())
    {
        cerr<<"next pattern"<<endl;
        nextPattern();
    }
}


void Phase::goToNextPhase()
{
    if(m_name=="still")
    {
        m_name="easy";
    }
    else if(m_name=="easy")
    {
        m_name="medium";
    }
    else if(m_name=="medium")
    {
        m_name="hard";
    }

    iniMap();
}

void Phase::erase()
{
    for(unsigned int i=0,count=m_patternQueue.size();i<count;i++)
        delete m_patternQueue[i];
    m_patternQueue.clear();

    m_pattern=NULL;
}








