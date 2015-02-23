#ifndef LIFEBAR_H_INCLUDED
#define LIFEBAR_H_INCLUDED
#include "Video.h"
#include "Player.h"

class LifeBar
{
public:
    LifeBar();
    void ini();
    void draw();
    void update(double functionTime, Player* p);
private:
    Texture* m_texture;
    double m_currentLife;
    double m_maxLife;

    double m_barWidth;
    double m_barHeight;
};


#endif // LIFEBAR_H_INCLUDED
