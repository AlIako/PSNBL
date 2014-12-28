#ifndef PATENDPHASE_H_INCLUDED
#define PATENDPHASE_H_INCLUDED
#include "Pattern.h"

class PatEndPhase: public Pattern
{
    public:
    PatEndPhase();


    virtual void ini(double startZ, std::vector<Object*>* objects);

    private:
};



#endif // PATENDPHASE_H_INCLUDED
