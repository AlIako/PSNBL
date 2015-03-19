#ifndef LIFEBAR_H_INCLUDED
#define LIFEBAR_H_INCLUDED
#include "Video.h"
#include "Object.h"

class LifeBar
{
public:
    LifeBar();
    void ini();
    void draw();
    void update(double functionTime, Object* o);

    void setPos(Vector3D p){m_position=p;}
    Vector3D getPos(){return m_position;}

    void setColor(Vector3D c){m_color=c;}
private:
    Texture* m_texture;
    double m_currentLife;
    double m_maxLife;

    double m_barWidth;
    double m_barHeight;

    Vector3D m_position;

    Vector3D m_color;
};


#endif // LIFEBAR_H_INCLUDED
