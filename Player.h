#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <cmath>
#include "Character.h"
#include "Rope.h"

enum DIRECTION { DOWN, LEFT, UP, RIGHT, KEY_E};

class Player: public Object
{
    public:
    Player();


    virtual void update(double functionTime);

    virtual void ini();
    virtual void draw();

    void jump();

    void pullUpRope();
    void linkRope(Rope* p);
    void unlinkRope();
    bool hookedToRope();

    void pressKey(DIRECTION k, bool pressed);

    void move();

    virtual void resurrect();

    private:
    Texture* m_texture;
    bool m_pressed[4];

    Rope* m_rope;

    bool m_jumping;
};

#endif // PLAYER_H_INCLUDED
