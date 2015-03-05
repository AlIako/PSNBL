#ifndef PATNEW_H_INCLUDED
#define PATNEW_H_INCLUDED
#include "Pattern.h"

class PatNew: public Pattern
{
    public:
    PatNew();


    virtual void ini(double startZ, std::vector<Object*>* objects);

    private:
};



#endif // PATNEW_H_INCLUDED
