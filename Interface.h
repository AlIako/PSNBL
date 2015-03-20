#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include "LifeBar.h"
#include "Crosshair.h"
#include "Texte.h"
#include "Object2D.h"

class Interface
{
public:
    static Interface* getInstance();

    void ini();
    void draw();
    void drawScreenEffect(std::string path);
    void update(double functionTime);

    void warning(string path, double speed=0.1, double timeStay=3000);


    void setTarget(Player* p) {m_target=p;}
    Player* getTarget() {return m_target;}
    void setMode(std::string m) {m_mode=m;}
    void setTargetBoss(Object* p) {m_targetBoss=p;}

    void setFPS(int fps);

    void close();


    Crosshair* getCrosshair(){return &m_crosshair;}

private:
    Interface();
    static Interface* m_instance;

    bool initalized;
    freetype::font_data m_font;

    std::string m_mode;

    Player* m_target;
    LifeBar m_lifebar;
    Crosshair m_crosshair;

    Object* m_targetBoss;
    LifeBar m_lifebarBoss;

    Texte m_playerName;
    Texte m_fps;


    bool m_goWarning;
    double m_warningSpeed;
    double m_warningTime;
    Object2D m_warning;
    GTime time_since_warning;
};


#endif // INTERFACE_H_INCLUDED
