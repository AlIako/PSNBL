#ifndef PATLETSGO_H_INCLUDED
#define PATLETSGO_H_INCLUDED
#include "Pattern.h"

class PatLetsGo: public Pattern
{
    public:
    PatLetsGo();


    virtual void ini(double startZ, std::vector<Object*>* objects);

    private:
};



#endif // PATLETSGO_H_INCLUDED
