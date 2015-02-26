#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED
#include "GTime.h"

class State
{
public:
    State();


    std::string getName() {return m_name;}
private:
    string m_name;
    GTime m_duration;
    int m_startEffect;
};


#endif // STATE_H_INCLUDED
