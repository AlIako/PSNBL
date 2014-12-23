#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
#include "Object.h"

enum{COL_GRAVITY,COL_MOVEMENT_X,COL_MOVEMENT_Y};

class Collision
{
    public:
    Collision();

    void simulatePhysics(Object* o);
    void collisionReaction(Object* o);

    void testCollision(Object* o, Object* pointer);
    bool testCollisionColliding(Object* o);


    void setObjects(std::vector<Object*>* v) {m_objects=v;}

    bool isCollisionType(int t);
    bool collision() {return m_colliding.size()>0;}

    private:
    std::vector<Object*>* m_objects;
    std::vector<Object*> m_colliding;
    std::vector<int> m_types;
};


#endif // COLLISION_H_INCLUDED
