#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include "LifeBar.h"
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
    void setMode(std::string m) {m_mode=m;}

private:
    freetype::font_data m_font;

    std::string m_mode;

    Player* m_target;
    LifeBar m_lifebar;

    Texte m_playerName;
};


#endif // INTERFACE_H_INCLUDED
