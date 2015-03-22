#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include "Vector3D.h"
#include "GTexture.h"
#include "Lighting.h"
#include "Gmodel.h"
#include "GTime.h"
#include "DRDampingSpring.h"
#include "Online.h"
#include "Gsounds.h"
#include "Effects.h"
#include "Tracer.h"
class Object;
#include "Collision.h"

class Object
{
    public:
    Object();
    virtual ~Object(){};

    virtual void ini();
    virtual void draw();

    bool collision(Object* o);

    virtual void update(double functionTime);

    virtual void action(int type, Vector3D v);
    virtual void action(int type, Object* o=NULL);


    void move(Vector3D v) {m_position+=v;}
    void moveToDir();

    virtual void applyGravity();

    virtual void resurrect();
    virtual void loseLife(double value);

    void applyPhysics();
    virtual void applyPhysics(int x, int y, int z);

    bool collidedWithType(std::string t);
    bool collidedWithHookable();

    void rotaZDir();
    void rotate(Vector3D v) {m_rotation+=v; }

    bool onGround();
    Object* onTopOf() { return m_onTopOf;}


    virtual void readObj(ifstream* fichier1);
    virtual string writeObj();

    //set
    virtual void setPos(Vector3D v) {m_position=v;}
    virtual void setStartPos(Vector3D v) {m_startPosition=v;}
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
    void setIdOnline(int i) { m_idOnline=i;}
    void setOnlineName(std::string s) {m_onlineName=s;}
    void collide(std::vector<Object*> v, std::vector<int> t) {m_collided=true; m_colliding=v; m_colTypes=t;}
    void setSpeed(double s) {m_speed=s;}
    void setLife(double l) {m_life=l;}
    void setLifeMax(double l) {m_lifeMax=l;}
    void setHookable(bool h) {m_hookable=h;}
    void setVisible(bool v) {m_visible=v;}
    void setTexture(Texture* t){m_texture=t;}
    void setFT(int f){ft=f;}
    void setDeathCause(int d){m_deathCause=d;}
    void setActive(bool a){m_active=a;}

    //add
    void addVel(Vector3D v){m_velocity+=v;}


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
    double getLife() {return m_life; }
    double getLifeMax() {return m_lifeMax; }
    int getIdOnline() {return m_idOnline;}
    std::string getOnlineName() { return m_onlineName;}
    bool isHookable() { return m_hookable; }
    bool collided(){return m_collided;}
    double getSpeed(){return m_speed;}
    int getDeathCause() {return m_deathCause;}
    bool isActive() {return m_active;}

    protected:
    Texture* m_texture;

    Vector3D m_position;
    Vector3D m_rotation;
    Vector3D m_size;
    std::string m_type;
    std::string m_name;
    Vector3D m_direction;
    Vector3D m_velocity;
    Vector3D m_movementVelocity;
    Vector3D m_startPosition;

    bool m_visible;
    bool m_physical;
    bool m_transparency;
    bool m_block;
    bool m_destructible;
    double m_life;
    double m_lifeMax;
    bool m_active;

    double m_speed;

    double ft;//function time

    GTime last_lose_life;
    GTime time_since_ini;

    bool m_gravity;

    bool m_collided;
    std::vector<Object*> m_colliding;
    std::vector<int> m_colTypes;

    int m_idOnline;
    std::string m_onlineName;

    bool m_hookable;

    Object* m_onTopOf;

    int m_deathCause;
};

#endif // OBJECT_H_INCLUDED
