#ifndef ROPE_H_INCLUDED
#define ROPE_H_INCLUDED
#include "Object.h"

class Rope: public Object
{
    public:
    Rope();
    void ini(Vector3D start, Vector3D dir);

    virtual void update(double functionTime);
    virtual void pullMe(Object* o);
    virtual void ini();
    virtual void draw();

    void setNowDistance();

    void pullUp();
    void pullDown();

    void linkToObject(Object* o) {linkedTo=o;}
    void unlink();

    bool isHooked() {return m_hooked;}

    virtual void setPos(Vector3D v) {m_position=v;m_start=m_position;}
    double getDistance(){return m_distance;}

    private:
    Texture* m_texture;
    bool m_hooked;

    Vector3D m_start;
    Vector3D m_end;
    double m_distance;

    bool m_smallBoost;

    Object* linkedTo;
    Object simulLinked;
};


#endif // ROPE_H_INCLUDED
