#ifndef PATHOOKAROUND_H_INCLUDED
#define PATHOOKAROUND_H_INCLUDED
#include "Pattern.h"

class PatHookAround: public Pattern
{
    public:
    PatHookAround();


    virtual void ini(double startZ, std::vector<Object*>* objects);

    private:
};



#endif // PATHOOKAROUND_H_INCLUDED
