#ifndef PATMIDBLOCKS_H_INCLUDED
#define PATMIDBLOCKS_H_INCLUDED
#include "Pattern.h"

class PatMidBlocks: public Pattern
{
    public:
    PatMidBlocks();


    virtual void ini(double startZ, std::vector<Object*>* objects);

    private:
};



#endif // PATMIDBLOCKS_H_INCLUDED
