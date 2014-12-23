#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <cmath>
#include "Character.h"

enum DIRECTION { DOWN, LEFT, UP, RIGHT};

class Player: public Object
{
    public:
    Player();
    virtual void ini();
    virtual void draw();

    void pressKey(DIRECTION k, bool pressed);

    void move();

    virtual void resurrect();

    private:
    Texture* m_texture;
    bool m_pressed[4];
};

#endif // PLAYER_H_INCLUDED
