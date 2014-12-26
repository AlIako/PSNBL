#ifndef PATSTILL_H_INCLUDED
#define PATSTILL_H_INCLUDED
#include "Pattern.h"

class PatStill: public Pattern
{
    public:
    PatStill();

    virtual void ini(double startZ, std::vector<Object*>* objects);

    private:
};


#endif // PATSTILL_H_INCLUDED
