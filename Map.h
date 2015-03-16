#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <vector>
#include "Collision.h"
#include "Player.h"
#include "Wall.h"
#include "Lava.h"
#include "Rope.h"
#include "Phase.h"
#include "Crosshair.h"

enum{PHASE_LOBBY,PHASE_EASY,PHASE_MEDIUM,PHASE_HARD};
enum{PAT_ONE,PAT_TWO,PAT_THREE,PAT_FOUR};

class Map
{
    public:
    Map();

    void ini(string path="");
    void draw();

    void createWalls();

    Rope* createRope(Vector3D start, Vector3D target);

    void update(double functionTime);
    void updateMap();
    void applyGravity(Object* o);
    void applyPhysics(Object* o);

    void simulateRopeForCrosshair(Player* p, Vector3D target, Crosshair* ch);

    void translateAll(Vector3D t);

    void restart();
    void erase();

    void increaseLavaSpeed();
    void setLavaLevel(double z);
    double getLavaLevel();
    Object* getLava();

    Phase* getPhase() {return &m_phase;}
    std::vector<Object*>* getObjects() {return &m_objects;}

    void loadPat(string path,double zOff=0);
    void saveMap(string path);

    void deleteLastObj();

    vector<Player*>* playerList;


    //for editor
    double editor_highestZ;
    double editor_nextZ;


    private:
    std::vector<Object*> m_objects;
    double ft;//function time

    Phase m_phase;



};


#endif // MAP_H_INCLUDED
