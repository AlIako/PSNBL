#include "PatEasy.h"



PatEasy::PatEasy()
{
    m_name="PatEasy";
}

void PatEasy::ini(double startZ, std::vector<Object*>* objects)
{
    Pattern::ini(startZ, objects);


    loadPattern();

    m_highestZ=startZ;
    m_highestZ+=200;
}




