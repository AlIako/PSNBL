#include "Phase.h"





Phase::Phase()
{
    m_name="still";

    highestZ=-100;

    m_pattern=NULL;

    m_lavaspeed=0;

    m_fogdistancestart=100;
    m_fogdistanceend=300;
    m_fogr=0.0f;
    m_fogg=0.0f;
    m_fogb=0.0f;

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

    if(!Online::getInstance()->inControl())
        m_name="waitingToReceive";
}


void Phase::nextPattern()
{
    //delete first pattern from queue
    if(m_patternQueue.size()>0)
    {
        delete m_patternQueue[0];
        m_patternQueue.erase(m_patternQueue.begin());
    }
    //size changed so check again
    if(m_patternQueue.size()>0)
    {
        //take first pattern from queue
        m_pattern=m_patternQueue[0];

        //apply pattern
        m_pattern->start();
    }
    else m_pattern=NULL;


    /*
    //if serv or solo: add pattern to queue
    if(Online::getInstance()->inControl())
        addPatternToQueue();*/
}



void Phase::update(double functionTime)
{
    if(m_pattern!=NULL)
    {
        m_pattern->update(functionTime);
        if(m_pattern->finished())
        {
            cerr<<"next pattern"<<endl;
            nextPattern();

            if(Online::getInstance()->inControl() && m_pattern==NULL)//if all patterns are finished
            {
                //go to a next phase
                goToNextPhase();
            }
        }
    }
    else if(m_patternQueue.size()>0)
    {
        m_pattern=m_patternQueue[0];
        m_pattern->start();
    }
}


void Phase::goToNextPhase()
{
    if(m_name=="waitingToReceive")
        m_name="still";
    else if(m_name=="still")
    {
        m_name="easy";
    }
    else if(m_name=="easy")
    {
        m_name="medium";
    }
    else if(m_name=="medium")
    {
        m_name="dark";
    }
    else if(m_name=="dark")
    {
        m_name="hard";
    }
    else m_name="still";//just to be sure

    iniMap();
}

void Phase::iniPhaseProperties()
{
    m_lavaspeed=0.1;
    m_fogdistancestart=100;
    m_fogdistanceend=300;
    m_fogr=0.0f;
    m_fogg=0.0f;
    m_fogb=0.0f;

    if(m_name=="still")
    {
        m_lavaspeed=0;
    }
    else if(m_name=="easy")
    {
        m_lavaspeed=0.1;
    }
    else if(m_name=="medium")
    {
        m_lavaspeed=0.4;
        m_fogdistancestart=50;
        m_fogdistanceend=200;
        m_fogr=0.7f;
        m_fogg=0.1f;
        m_fogb=0.1f;
    }
    else if(m_name=="dark")
    {
        m_lavaspeed=0.3;
        m_fogdistancestart=0;
        m_fogdistanceend=45;
        m_fogr=0.0f;
        m_fogg=0.0f;
        m_fogb=0.0f;
    }
    else if(m_name=="hard")
    {
        m_lavaspeed=0.7;
        m_fogdistancestart=10;
        m_fogdistanceend=150;
        m_fogr=1.0f;
        m_fogg=0.0f;
        m_fogb=0.0f;
    }

    m_lava->setSpeed(m_lavaspeed);

    if(Video::getInstance()!=NULL)
        Video::getInstance()->getFog()->setTarget(m_fogdistancestart,m_fogdistanceend,m_fogr,m_fogg,m_fogb);
}

void Phase::iniMap()
{
    cerr<<"ini mapphase "<<m_name<<endl;

    iniPhaseProperties();

    m_patternQueue.clear();
    if(Online::getInstance()->inControl())
    {
        int randomizer=myIntRand(0,100);
        //ini patterns depending on which phase
        if(m_name=="still")//lobby like, lava rly slow
        {
            addPatternToQueue(1);
            //addPatternToQueue(6);
        }
        else if(m_name=="easy")
        {
            for(int i=0;i<2-1;i++)
            {
                randomizer=myIntRand(0,400);

                addPatternToQueue(9);
                //next pattern are random
                /*if(randomizer>300)
                    addPatternToQueue(2);
                else if(randomizer>200)
                    addPatternToQueue(3);
                else if(randomizer>100)
                    addPatternToQueue(6);
                else if(randomizer>0)
                    addPatternToQueue(4);*/
            }
        }
        else if(m_name=="medium")
        {
            for(int i=0;i<2;i++)
            {
                randomizer=myIntRand(0,400);
                //next pattern are random
                if(randomizer>300)
                    addPatternToQueue(2);
                else if(randomizer>200)
                    addPatternToQueue(3);
                else if(randomizer>100)
                    addPatternToQueue(7);
                else if(randomizer>0)
                    addPatternToQueue(4);
            }
        }
        else if(m_name=="dark")
        {
            for(int i=0;i<3;i++)
            {
                randomizer=myIntRand(0,400);
                //next pattern are random
                if(randomizer>300)
                    addPatternToQueue(2);
                else if(randomizer>200)
                    addPatternToQueue(3);
                else if(randomizer>100)
                    addPatternToQueue(7);
                else if(randomizer>0)
                    addPatternToQueue(4);
            }
        }
        else if(m_name=="hard")
        {
            for(int i=0;i<4;i++)
            {
                randomizer=myIntRand(0,400);
                //next pattern are random
                if(randomizer>300)
                    addPatternToQueue(2);
                else if(randomizer>200)
                    addPatternToQueue(3);
                else if(randomizer>100)
                    addPatternToQueue(6);
                else if(randomizer>0)
                    addPatternToQueue(4);
            }
        }

        //always at the end of a phase
        //addPatternToQueue(5);

        //start with first pattern in queue
        m_pattern=m_patternQueue[0];
        m_pattern->start();


        //send that shit
        if(Online::getInstance()->inControl())
        {
            if(Online::getInstance()!=NULL && Online::getInstance()->active())
            {
                infosSocket s;
                s.confirmationID=Online::getInstance()->nextConfirmationID();
                s.type=8;
                s.variable[0]=0;
                s.variable[1]=m_lava->getSize().Z;//lava level
                s.variable[2]=m_patternQueue[m_patternQueue.size()-1]->getStartZ();
                for(unsigned int i=0;i<m_patternQueue.size();i++)
                {
                    s.variable[3+i]=m_patternQueue[i]->getPID();
                    cerr<<"sending pattern "<< s.variable[3+i] << " to clients"<<endl;
                }
                s.variable[3+m_patternQueue.size()]=-1;
                Online::getInstance()->sendSocket(s);
            }
        }
    }
}

void Phase::addPatternToQueue(int p)
{
    if(p==1)
    {
        m_patternQueue.push_back(new PatStill());
    }
    else if(p==2)
    {
        m_patternQueue.push_back(new PatBigBlocks());
    }
    else if(p==3)
    {
        m_patternQueue.push_back(new PatBeams());
    }
    else if(p==4)
    {
        m_patternQueue.push_back(new PatMidBlocks());
    }
    else if(p==5)
    {
        m_patternQueue.push_back(new PatEndPhase());
    }
    else if(p==6)
    {
        m_patternQueue.push_back(new PatLetsGo());
    }
    else if(p==7)
    {
        m_patternQueue.push_back(new PatHookAround());
    }
    else if(p==8)
    {
        m_patternQueue.push_back(new PatEasy());
    }
    else if(p==9)
    {
        m_patternQueue.push_back(new PatNew());
    }

    iniLastPattern();
}


void Phase::iniLastPattern()
{
    //ini those new patterns but dont start them yet
    if(m_patternQueue.size()>0)
    {
        m_patternQueue[m_patternQueue.size()-1]->ini(highestZ,m_objects);
        highestZ=m_patternQueue[m_patternQueue.size()-1]->getHighestZ();
    }
}












void Phase::erase()
{
    for(unsigned int i=0,count=m_patternQueue.size();i<count;i++)
        delete m_patternQueue[i];
    m_patternQueue.clear();

    m_pattern=NULL;

    m_name="still";
}








