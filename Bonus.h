#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED
#include "Object.h"

class Bonus: public Object
{
    public:
    Bonus();

    virtual void ini();
    virtual void draw();

    private:
};

#endif // BONUS_H_INCLUDED
