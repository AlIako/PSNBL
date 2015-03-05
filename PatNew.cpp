#include "PatNew.h"



PatNew::PatNew()
{
    m_name="PatNew";
}

void PatNew::ini(double startZ, std::vector<Object*>* objects)
{
    Pattern::ini(startZ, objects);


    loadPattern();

    m_highestZ=startZ;
    m_highestZ+=20;
}




