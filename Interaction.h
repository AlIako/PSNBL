#ifndef INTERACTION_H_INCLUDED
#define INTERACTION_H_INCLUDED
#include <math.h>
#include <SDL/SDL.h>
#include <vector>
#include <string>
#include "GTime.h"

struct coord2d
{
    int x;
    int y;
};

class Interaction
{
    public:
    Interaction();
    void clickGauche(bool down,int x, int y);
    void update();
    bool grab();
    bool clicked();
    bool appuye();

    private:
    bool m_grab;
    bool m_click;
    bool m_appuyer;
    GTime lastclick;
    coord2d lastclickcoord;
};

#endif // INTERACTION_H_INCLUDED
