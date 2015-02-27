#ifndef PATEASY_H_INCLUDED
#define PATEASY_H_INCLUDED
#include "Pattern.h"

class PatEasy: public Pattern
{
    public:
    PatEasy();


    virtual void ini(double startZ, std::vector<Object*>* objects);

    private:
};



#endif // PATEASY_H_INCLUDED
