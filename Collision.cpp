#include "Collision.h"



Collision::Collision()
{
    m_types.clear();
    m_colliding.clear();
}






void Collision::simulatePhysics(Object* o)
{
    //do a first simulation and get all colliding objects
    Object simO=*o;
    simO.applyPhysics();
    testCollision(&simO,o);

    //if there was a collision, check what movement caused it (test only with colliding objects)
    if(collision())
    {
        //movement blocking

        //test gravity
        simO=*o;
        simO.applyPhysics(0,0,1);
        if(testCollisionColliding(&simO))
            m_types.push_back(COL_GRAVITY);
        //test movement x
        simO=*o;
        simO.applyPhysics(1,0,0);
        if(testCollisionColliding(&simO))
            m_types.push_back(COL_MOVEMENT_X);
        //test movement y
        simO=*o;
        simO.applyPhysics(0,1,0);
        if(testCollisionColliding(&simO))
            m_types.push_back(COL_MOVEMENT_Y);



        //only authorize physics where there was no collision
        simO=*o;
        //reaction to collision
        if(isCollisionType(COL_GRAVITY))//collision because of gravity
        {
            simO.setVel(Vector3D(simO.getVel().X,simO.getVel().Y,simO.getVel().Z*(-0.3)));
        }
        if(isCollisionType(COL_MOVEMENT_X))//collision because of movement x
        {
            simO.setVel(Vector3D(simO.getVel().X*(-0.5),simO.getVel().Y,simO.getVel().Z));
        }
        if(isCollisionType(COL_MOVEMENT_Y))//collision because of movement y
        {
            simO.setVel(Vector3D(simO.getVel().X,simO.getVel().Y*(-0.5),simO.getVel().Z));
        }
        //reaction to non collision
        if(!isCollisionType(COL_GRAVITY))
            simO.applyPhysics(0,0,1);
        if(!isCollisionType(COL_MOVEMENT_X))
            simO.applyPhysics(1,0,0);
        if(!isCollisionType(COL_MOVEMENT_Y))
            simO.applyPhysics(0,1,0);


        //apply specific collision behaviour
        collisionReaction(&simO);
        simO.collide();

    }

    //apply changes to original object
    *o=simO;
}

void Collision::collisionReaction(Object* o)
{
    for(unsigned int i=0, count=m_colliding.size();i<count;i++)
    {
        if(m_colliding[i]->getType()=="lava")
        {
            if(o->getDestructible())
                o->loseLife(1);
        }
    }
}



void Collision::testCollision(Object* o, Object* pointer)
{
    m_colliding.clear();
    for(unsigned int i=0, count=(*m_objects).size();i<count;i++)
        if((*m_objects)[i]!=pointer && o->collision((*m_objects)[i]))
            m_colliding.push_back((*m_objects)[i]);
}


bool Collision::testCollisionColliding(Object* o)
{
    for(unsigned int i=0, count=m_colliding.size();i<count;i++)
        if(m_colliding[i]->getBlock() && o->collision(m_colliding[i]))
            return true;
    return false;
}







bool Collision::isCollisionType(int t)
{
    for(unsigned int i=0, count=m_types.size();i<count;i++)
        if(t==m_types[i])
            return true;
    return false;
}












