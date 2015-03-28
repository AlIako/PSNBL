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
    virtual void updateMulti(double functionTime);

    virtual void ini();
    virtual void draw();

    virtual void applyGravity();

    void playGroundSound();


    bool jump();

    void pullUpRope();
    void linkRope(Rope* p);
    void unlinkRope();
    bool hookedToRope();
    bool ropeHooked();

    void pressKey(DIRECTION k, bool pressed);

    void move();
    void moveXY(Vector3D* vel);

    void updateRope();

    virtual void resurrect();

    //set
    void setGasing(bool g){m_gasing=g;}
    void setTestMode(bool t){testMode=t;}

    //get
    bool getGasing() {return m_gasing;}
    Rope* getRope() {return m_rope;}

    //spells
    void addSpell(Spell* s);
    Spell* getSpell(string s);
    vector<Spell*>* getSpells(){return &m_spells;}

    private:
    Vector3D m_startpos;

    Texture* m_textureDead;
    bool m_pressed[5];

    Rope* m_rope;

    GTime sound_step;

    double m_maxspeed;

    bool m_jumping;
    bool m_gasing;

    vector<Spell*> m_spells;

    bool testMode;

    bool m_inLava;
};

#endif // PLAYER_H_INCLUDED
