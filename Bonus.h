#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED
#include "Object.h"

class Bonus: public Object
{
    public:
    Bonus();

    virtual void ini();
    virtual void update(double functionTime);
    virtual void draw();

    private:
    Texture* m_texture;
};

#endif // BONUS_H_INCLUDED
