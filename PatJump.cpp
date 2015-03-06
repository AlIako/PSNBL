#include "PatJump.h"



PatJump::PatJump()
{
    m_name="PatJump";
}

void PatJump::ini(double startZ, std::vector<Object*>* objects)
{
    Pattern::ini(startZ, objects);


    loadPattern();

    calculHighestZ();
    m_highestZ-=4;
    m_nextZ=m_highestZ+5;
}




