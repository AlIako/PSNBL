#ifndef PATBIGBLOCKS_H_INCLUDED
#define PATBIGBLOCKS_H_INCLUDED
#include "Pattern.h"

class PatBigBlocks: public Pattern
{
    public:
    PatBigBlocks();


    virtual void ini(double startZ, std::vector<Object*>* objects);

    private:
};



#endif // PATBIGBLOCKS_H_INCLUDED
