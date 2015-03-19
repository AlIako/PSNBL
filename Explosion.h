#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED
#include "Vector3D.h"
#include "Gtexture.h"
#include "Lighting.h"
#include <vector>

struct particle
{
    double life;
    Vector3D position;
    Vector3D speed;
    Vector3D direction;
    Vector3D rotation;
    double size;
};

class Explosion
{
public:
    Explosion();

    void ini(string type);
    void start(string type);

    void update(double functionTime);
    void draw();

    bool over(){return m_over;}


    //sets
    void setPos(Vector3D v) {m_position=v;}
    void setSize(Vector3D v) {m_size=v;}

    //gets
    Vector3D getPos() {return m_position;}
    Vector3D getSize() {return m_size;}

private:
    Texture* m_texture;

    Vector3D m_position;
    Vector3D m_size;

    double m_speed;
    int m_time;
    std::vector<particle> particles;
    bool m_over;
};

#endif // EXPLOSION_H_INCLUDED
