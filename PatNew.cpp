#include "PatNew.h"



PatNew::PatNew()
{
    m_name="PatNew";
}

void PatNew::ini(double startZ, std::vector<Object*>* objects)
{
    //startZ-=19;
    Pattern::ini(startZ, objects);


    loadPattern();

    calculHighestZ();
    //m_highestZ=startZ;
    //m_highestZ+=20;
}




