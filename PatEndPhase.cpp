#include "PatEndPhase.h"



PatEndPhase::PatEndPhase()
{
    m_name="PatEndPhase";
}

void PatEndPhase::ini(double startZ, std::vector<Object*>* objects)
{
    Pattern::ini(startZ, objects);

    //blocks

    unsigned int ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->setName("finalBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(0,0,startZ+15));
    (*m_objects)[ind]->setSize(Vector3D(4,4,2));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Bonus());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->online=online;
    (*m_objects)[ind]->setName("rez");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(0,0,startZ+15+4));

    m_highestZ=startZ;
}




