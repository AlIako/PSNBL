#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <vector>
#include "Collision.h"
#include "Player.h"
#include "Wall.h"
#include "Lava.h"
#include "Rope.h"
#include "Phase.h"

enum{PHASE_LOBBY,PHASE_EASY,PHASE_MEDIUM,PHASE_HARD};
enum{PAT_ONE,PAT_TWO,PAT_THREE,PAT_FOUR};

class Map
{
    public:
    Map();

    void ini();
    void draw();

    Rope* createRope(Vector3D start, Vector3D target);

    void update(double functionTime);
    void updateMap();
    void applyGravity(Object* o);
    void applyPhysics(Object* o);

    void restart();
    void erase();

    void addPatternToQueue(int p);
    void setLavaLevel(double z);
    double getLavaLevel();

    Phase* getPhase() {return &m_phase;}

    //public attributes
    bool m_incontrol;
    Online* online;
    GTexture* gtext;

    vector<Player*>* playerList;

    private:
    std::vector<Object*> m_objects;
    double ft;//function time

    Phase m_phase;

};


#endif // MAP_H_INCLUDED
