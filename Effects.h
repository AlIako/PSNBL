#ifndef EFFECTS_H_INCLUDED
#define EFFECTS_H_INCLUDED
#include "GTexture.h"
#include "Vector3D.h"
#include "Explosion.h"

class Effects
{
public:
    static Effects* getInstance();

    void update(double functionTime);
    void draw();

    void addExplosion(Vector3D position);

private:
    Effects();
    static Effects* m_instance;

    vector<Explosion> m_explosions;
};

#endif // EFFECTS_H_INCLUDED
