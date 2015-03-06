#ifndef PATJUMP_H_INCLUDED
#define PATJUMP_H_INCLUDED
#include "Pattern.h"

class PatJump: public Pattern
{
    public:
    PatJump();


    virtual void ini(double startZ, std::vector<Object*>* objects);

    private:
};



#endif // PATJUMP_H_INCLUDED
