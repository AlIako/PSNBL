#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include "Vector3D.h"
#include "GTexture.h"
#include "GTime.h"

class Object
{
    public:
    Object();

    virtual void ini();
    virtual void draw();

    bool collision(Object* o);

    virtual void update(double functionTime);

    void move(Vector3D v) {m_position+=v;}
    void applyGravity();

    virtual void resurrect();
    void loseLife(double value);

    void applyPhysics();
    void applyPhysics(int x, int y, int z);

    void rotate(Vector3D v) {m_rotation+=v; }

    //set
    void setPos(Vector3D v) {m_position=v;}
    void setRot(Vector3D v) {m_rotation=v;}
    void setDir(Vector3D v) {m_direction=v;}
    void setSize(Vector3D v) {m_size=v;}
    void setVel(Vector3D v) {m_velocity=v;}
    void setType(std::string s) {m_type=s;}
    void setPhysical(bool p) {m_physical=p;}
    void setTransparency(bool t) {m_transparency=t;}
    void setBlock(bool b) {m_block=b;}
    void setDestructible(bool b) {m_destructible=b;}
    void collide() {m_collided=true;}

    //get
    Vector3D getPos() {return m_position;}
    Vector3D getRot() {return m_rotation;}
    Vector3D getSize() {return m_size;}
    Vector3D getVel() {return m_velocity;}
    Vector3D getDir() {return m_direction;}
    std::string getType() {return m_type;}
    bool getPhysical() {return m_physical; }
    bool getTransparency() {return m_transparency; }
    bool getBlock() {return m_block; }
    bool getDestructible() {return m_destructible; }
    double getLife() {return m_life; }

    //public attributes
    GTexture* gtext;

    protected:
    Vector3D m_position;
    Vector3D m_rotation;
    Vector3D m_size;
    std::string m_type;
    Vector3D m_direction;
    Vector3D m_velocity;

    bool m_physical;
    bool m_transparency;
    bool m_block;
    bool m_destructible;
    double m_life;

    double m_speed;

    double ft;//function time

    GTime last_lose_life;

    bool m_collided;
};

#endif // OBJECT_H_INCLUDED
