#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include "Vector3D.h"
#include "GTexture.h"
#include "GTime.h"
#include "DRDampingSpring.h"
#include "Online.h"

class Object
{
    public:
    Object();
    virtual ~Object(){};

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

    bool collidedWithType(std::string t);
    bool collidedWithHookable();

    void rotate(Vector3D v) {m_rotation+=v; }

    //set
    void setPos(Vector3D v) {m_position=v;}
    void setRot(Vector3D v) {m_rotation=v;}
    void setDir(Vector3D v) {m_direction=v;}
    void setSize(Vector3D v) {m_size=v;}
    void setVel(Vector3D v) {m_velocity=v;}
    void setType(std::string s) {m_type=s;}
    void setName(std::string s) {m_name=s;}
    void setPhysical(bool p) {m_physical=p;}
    void setTransparency(bool t) {m_transparency=t;}
    void setBlock(bool b) {m_block=b;}
    void setDestructible(bool b) {m_destructible=b;}
    void setOnground(bool b) {m_onground=b;}
    void setIdOnline(int i) { m_idOnline=i;}
    void setOnlineName(std::string s) {m_onlineName=s;}
    void collide(std::vector<Object*> v, std::vector<int> t) {m_collided=true; m_colliding=v; m_colTypes=t;}
    void setSpeed(double s) {m_speed=s;}
    void setLife(double l) {m_life=l;}
    void setHookable(bool h) {m_hookable=h;}


    //get
    Vector3D getPos() {return m_position;}
    Vector3D getRot() {return m_rotation;}
    Vector3D getSize() {return m_size;}
    Vector3D getVel() {return m_velocity;}
    Vector3D getDir() {return m_direction;}
    std::string getType() {return m_type;}
    std::string getName() {return m_name;}
    bool getPhysical() {return m_physical; }
    bool getTransparency() {return m_transparency; }
    bool getBlock() {return m_block; }
    bool getDestructible() {return m_destructible; }
    bool getOnground() {return m_onground; }
    double getLife() {return m_life; }
    int getIdOnline() {return m_idOnline;}
    std::string getOnlineName() { return m_onlineName;}
    bool isHookable() { return m_hookable; }

    protected:
    Vector3D m_position;
    Vector3D m_rotation;
    Vector3D m_size;
    std::string m_type;
    std::string m_name;
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

    bool m_gravity;
    bool m_onground;

    bool m_collided;
    std::vector<Object*> m_colliding;
    std::vector<int> m_colTypes;

    int m_idOnline;
    std::string m_onlineName;

    bool m_hookable;
};

#endif // OBJECT_H_INCLUDED
