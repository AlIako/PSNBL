#include "PatMidBlocks.h"



PatMidBlocks::PatMidBlocks()
{
    m_name="PatMidBlocks";
}

void PatMidBlocks::ini(double startZ, std::vector<Object*>* objects)
{
    Pattern::ini(startZ, objects);

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

    calculHighestZ();
}




