#include "Interaction.h"


Interaction::Interaction()
{
    m_grab=false;
    m_click=false;
    m_appuyer=false;
    lastclick.reset();
    lastclickcoord.x=0;
    lastclickcoord.y=0;
}


void Interaction::clickGauche(bool down,int x, int y)
{
    //bouton appuyé (et il letait pas avant)
    if(down && !m_appuyer)
    {
        lastclick.reset();
        m_appuyer=true;
        lastclickcoord.x=x;
        lastclickcoord.y=y;
    }
    else if(!down && m_appuyer)//bouton relaché apres qu'il ait été appuyé
    {
        SDL_WarpMouse(lastclickcoord.x, lastclickcoord.y);
        m_grab=false;
        m_appuyer=false;
        lastclick.couler();
        //si le temps depuis qu'on a appuyé est inferieur a 100ms
        if(lastclick.timePast()<200 && fabs(lastclickcoord.x-x)+fabs(lastclickcoord.y-y)<30)
            m_click=true;
    }
    //bouton appuyé (et il letait avant)
    else if(down && m_appuyer)
    {
        m_grab=true;
        m_click=false;
    }
}
void Interaction::update()
{
    m_click=false;
    m_grab=false;
}
bool Interaction::grab()
{
    return m_grab;
}
bool Interaction::clicked()
{
    return m_click;
}
bool Interaction::appuye()
{
    return m_appuyer;
}
