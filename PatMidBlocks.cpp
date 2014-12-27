#include "PatMidBlocks.h"



PatMidBlocks::PatMidBlocks()
{
    m_name="PatMidBlocks";
}

void PatMidBlocks::ini(double startZ, std::vector<Object*>* objects)
{
    Pattern::ini(startZ, objects);

    m_lavaspeed=1;
    m_fogdistancestart=10;
    m_fogdistanceend=100;
    m_fogr=1.0f;
    m_fogg=0.0f;
    m_fogb=0.0f;

    //blocks
    unsigned int ind=(*m_objects).size();
    for(int i=0;i<10;i++)
    {
        ind=(*m_objects).size();
        (*m_objects).push_back(new Block());
        (*m_objects)[ind]->gtext=gtext;
        (*m_objects)[ind]->ini();
        (*m_objects)[ind]->setPos(Vector3D(0,0,startZ+30*i));
        (*m_objects)[ind]->setSize(Vector3D(4,4,4));
    }

    /*ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(10,0,startZ+40));
    (*m_objects)[ind]->setSize(Vector3D(8,8,12));*/


    calculHighestZ();
}




