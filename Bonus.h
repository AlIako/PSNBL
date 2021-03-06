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
    virtual void loseLife(double value);

    virtual string writeObj();

    private:
    Texture* m_texture;
    string meshPath;
};

#endif // BONUS_H_INCLUDED
