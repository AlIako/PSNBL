#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
class Collision;
#include "Object.h"

enum{COL_GRAVITY,COL_MOVEMENT_X,COL_MOVEMENT_Y};

class Collision
{
    public:
    static Collision* getInstance();

    void simulatePhysics(Object* o);
    void collisionReaction(Object* o);

    bool testCollision(Object* o);
    void testCollision(Object* o, Object* pointer);
    bool testCollisionColliding(Object* o);


    void setObjects(std::vector<Object*>* v) {m_objects=v;}

    void collide(Object* o);

    bool isCollisionType(int t);
    bool collision() {return m_colliding.size()>0;}

    private:
    Collision();
    static Collision* m_instance;

    std::vector<Object*>* m_objects;
    std::vector<Object*> m_colliding;
    std::vector<int> m_types;
};


#endif // COLLISION_H_INCLUDED
