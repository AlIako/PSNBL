#ifndef CROSSHAIR_H_INCLUDED
#define CROSSHAIR_H_INCLUDED
#include "Video.h"
#include "Player.h"

class Crosshair
{
public:
    Crosshair();
    void ini();
    void draw();
    void update(double functionTime);
    void setColor(int r, int g, int b){m_r=r;m_g=g;m_b=b;}
private:
    int m_r;
    int m_g;
    int m_b;
};


#endif // CROSSHAIR_H_INCLUDED
