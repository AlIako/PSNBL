#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include "Vector3D.h"
#include "Gtexture.h"

class Object
{
    public:
    Object();

    virtual void ini();
    virtual void draw();

    bool collision(Object* o);


    void move(Vector3D v) {m_position+=v;}
    void rotate(Vector3D v) {m_rotation+=v; }

    //set
    void setPos(Vector3D v) {m_position=v;}
    void setRot(Vector3D v) {m_rotation=v;}
    void setDir(Vector3D v) {m_direction=v;}
    void setSize(Vector3D v) {m_size=v;}
    void setType(std::string s) {m_type=s;}

    //get
    Vector3D getPos() {return m_position;}
    Vector3D getRot() {return m_rotation;}
    Vector3D getSize() {return m_size;}
    std::string getType() {return m_type;}

    //public attributes
    Gtexture* gtext;

    protected:
    Vector3D m_position;
    Vector3D m_rotation;
    Vector3D m_size;
    std::string m_type;
    Vector3D m_direction;

    double m_speed;
};

#endif // OBJECT_H_INCLUDED
