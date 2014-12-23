#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <vector>
#include "Collision.h"
#include "Player.h"
#include "Wall.h"
#include "Lava.h"

class Map
{
    public:
    Map();

    void ini();
    void draw();

    void update(double functionTime);
    void applyGravity(Object* o);
    void applyPhysics(Object* o);

    //public attributes
    GTexture* gtext;

    vector<Player*>* playerList;

    private:
    std::vector<Object*> m_objects;
    double ft;//function time

};


#endif // MAP_H_INCLUDED