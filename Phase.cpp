#include "Phase.h"





Phase::Phase()
{
    m_name="still";

    highestZ=-100;

    m_pattern=NULL;

    m_lavaspeed=0;

    m_fogdistancestart=500;
    m_fogdistanceend=800;
    m_fogr=0.0f;
    m_fogg=0.0f;
    m_fogb=0.0f;

    m_boostingLava=false;

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
    nextZ=highestZ*0;

    if(Online::getInstance()->active() && !Online::getInstance()->inControl())
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
            //cerr<<"next pattern"<<endl;
            nextPattern();

            //if next pattern is a boss, stop the lava
            if(m_pattern!=NULL && !m_boostingLava && m_pattern->getName().find("Boss")!=string::npos)
            {
                m_lavaspeed=0;
                m_lava->setSpeed(m_lavaspeed);
            }

            if((!Online::getInstance()->active() || Online::getInstance()->inControl()) && m_pattern==NULL)//if all patterns are finished
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
    m_boostingLava=false;
    m_lavaspeed=0.1;
    m_fogdistancestart=500;
    m_fogdistanceend=800;
    m_fogr=0.0f;
    m_fogg=0.0f;
    m_fogb=0.0f;

    if(m_name=="still")
    {
        m_lavaspeed=0;
    }
    else if(m_name=="tutorial")
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
        m_fogdistancestart=200;
        m_fogdistanceend=500;
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
    //cerr<<"ini mapphase "<<m_name<<endl;

    iniPhaseProperties();

    m_patternQueue.clear();
    if(!Online::getInstance()->active() || Online::getInstance()->inControl())
    {
        int randomizer=myIntRand(0,100);
        //ini patterns depending on which phase
        if(m_name=="still")//lobby like, lava rly slow
        {
            addPatternToQueue("PatStill");
            //addPatternToQueue(6);
        }
        else if(m_name=="easy")
        {
            randomizer=myIntRand(0,200);

            if(randomizer>100)
                addPatternToQueue("PatJump1");
            else if(randomizer>0)
                addPatternToQueue("PatJump2");

            randomizer=myIntRand(0,200);
            if(randomizer>100)
                addPatternToQueue("PatRope1");
            else if(randomizer>0)
                addPatternToQueue("PatRope2");


            randomizer=myIntRand(0,200);
            if(randomizer>100)
                addPatternToQueue("PatRopeJump1");
            else if(randomizer>0)
                addPatternToQueue("PatRopeJump2");

            randomizer=myIntRand(0,200);
            if(1||randomizer>100)
                addPatternToQueue("PatRopeFlux1");
            else if(randomizer>0)
                addPatternToQueue("PatRopeFlux2");


            addPatternToQueue("BossButan");
        }
        else if(m_name=="medium")
        {
            for(int i=0;i<2;i++)
            {
                randomizer=myIntRand(0,400);
                //next pattern are random
                if(randomizer>300)
                    addPatternToQueue("PatBigBlocks");
                else if(randomizer>200)
                    addPatternToQueue("PatBeams");
                else if(randomizer>100)
                    addPatternToQueue("PatHookAround");
                else if(randomizer>0)
                    addPatternToQueue("PatMidBlocks");
            }
        }
        else if(m_name=="dark")
        {
            for(int i=0;i<3;i++)
            {
                randomizer=myIntRand(0,400);
                //next pattern are random
                if(randomizer>300)
                    addPatternToQueue("PatBigBlocks");
                else if(randomizer>200)
                    addPatternToQueue("PatBeams");
                else if(randomizer>100)
                    addPatternToQueue("PatHookAround");
                else if(randomizer>0)
                    addPatternToQueue("PatMidBlocks");
            }
        }
        else if(m_name=="hard")
        {
            for(int i=0;i<4;i++)
            {
                randomizer=myIntRand(0,400);
                //next pattern are random
                if(randomizer>300)
                    addPatternToQueue("PatBigBlocks");
                else if(randomizer>200)
                    addPatternToQueue("PatBeams");
                else if(randomizer>100)
                    addPatternToQueue("PatLetsGo");
                else if(randomizer>0)
                    addPatternToQueue("PatMidBlocks");
            }
        }

        //always at the end of a phase
        //addPatternToQueue(5);

        //start with first pattern in queue
        if(m_patternQueue.size()>0)
        {
            m_pattern=m_patternQueue[0];
            m_pattern->start();
            sendPatternOnline();
        }
    }
}

void Phase::sendPatternOnline(int sendTo)
{
    //send that shit
    if(Online::getInstance()->active() && Online::getInstance()->inControl())
    {
        //send phase name
        infosSocket s;
        s.confirmationID=Online::getInstance()->nextConfirmationID();
        s.type=9;
        s.variable[0]=0;

        string strToCopy=m_name;
        strncpy( s.text, strToCopy.c_str(), strToCopy.size()+2 );
        s.text[strToCopy.size()+1]='\0';
        Online::getInstance()->sendSocket(s,sendTo);

        //send patterns
        s.confirmationID=Online::getInstance()->nextConfirmationID();
        s.type=8;
        s.variable[0]=0;
        s.variable[1]=m_lava->getSize().Z;//lava level
        s.variable[2]=m_patternQueue[m_patternQueue.size()-1]->getStartZ();
        for(unsigned int i=0;i<m_patternQueue.size();i++)
        {
            //s.variable[3+i]=m_patternQueue[i]->getPID();
            //cerr<<"sending pattern "<< s.variable[3+i] << " to clients"<<endl;

            s.confirmationID=Online::getInstance()->nextConfirmationID();

            s.variable[1]=m_patternQueue[i]->getStartZ();//lava level

            string strToCopy=m_patternQueue[i]->getName();
            strncpy( s.text, strToCopy.c_str(), strToCopy.size()+2 );
            s.text[strToCopy.size()+1]='\0';
            Online::getInstance()->sendSocket(s,sendTo);
            cerr<<"sending pattern "<< s.text << " to clients"<<endl;
        }
    }
}

void Phase::addPatternToQueue(string name, double startz)
{
    int ind=(int)m_patternQueue.size();
    m_patternQueue.push_back(new Pattern());
    m_patternQueue[ind]->setName(name);
    if(startz!=-1)
    {
        nextZ=startz;
        m_patternQueue[ind]->setStartZ(startz);
    }
    iniLastPattern();
}

void Phase::boostLava()
{
    m_boostingLava=true;
    m_lava->setSpeed(2);
}

void Phase::iniLastPattern()
{
    //ini those new patterns but dont start them yet
    if(m_patternQueue.size()>0)
    {
        m_patternQueue[m_patternQueue.size()-1]->ini(nextZ,m_objects);
        highestZ=m_patternQueue[m_patternQueue.size()-1]->getHighestZ();
        nextZ=m_patternQueue[m_patternQueue.size()-1]->getNextZ();

        cerr<<"nextZ: "<<nextZ<<endl;
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








