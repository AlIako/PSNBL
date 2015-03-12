#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include "LifeBar.h"
#include "Crosshair.h"
#include "Texte.h"

class Interface
{
public:
    Interface();
    void ini();
    void draw();
    void drawScreenEffect(std::string path);
    void update(double functionTime);


    void setTarget(Player* p) {m_target=p;}
    Player* getTarget() {return m_target;}
    void setMode(std::string m) {m_mode=m;}

    void setFPS(int fps);


    Crosshair* getCrosshair(){return &m_crosshair;}

private:
    freetype::font_data m_font;

    std::string m_mode;

    Player* m_target;
    LifeBar m_lifebar;
    Crosshair m_crosshair;

    Texte m_playerName;
    Texte m_fps;
};


#endif // INTERFACE_H_INCLUDED
