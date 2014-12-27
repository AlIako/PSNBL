#ifndef PATBEAMS_H_INCLUDED
#define PATBEAMS_H_INCLUDED
#include "Pattern.h"

class PatBeams: public Pattern
{
    public:
    PatBeams();


    virtual void ini(double startZ, std::vector<Object*>* objects);

    private:
};




#endif // PATBEAMS_H_INCLUDED
