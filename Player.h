#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <cmath>
#include "Character.h"
#include "Rope.h"
#include "SpellRope.h"
#include "SpellJump.h"
#include "SpellLongJump.h"
#include "SpellPullUp.h"
#include "SpellRopeBoost.h"

enum DIRECTION { DOWN, LEFT, UP, RIGHT, KEY_E};

class Player: public Object
{
    public:
    Player();
    virtual ~Player(){};


    virtual void update(double functionTime);

    virtual void ini();
    virtual void draw();


    void jump();

    void pullUpRope();
    void linkRope(Rope* p);
    void unlinkRope();
    bool hookedToRope();
    bool ropeHooked();

    void pressKey(DIRECTION k, bool pressed);

    void move();
    void moveXY(Vector3D* vel);

    virtual void resurrect();

    //set
    void setGasing(bool g){m_gasing=g;}

    //get
    bool getGasing() {return m_gasing;}

    //spells
    void addSpell(Spell* s);
    Spell* getSpell(string s);

    private:
    Vector3D m_startpos;

    Texture* m_texture;
    Texture* m_textureDead;
    bool m_pressed[5];

    Rope* m_rope;

    double m_maxspeed;

    bool m_jumping;
    bool m_gasing;

    vector<Spell*> m_spells;
};

#endif // PLAYER_H_INCLUDED
