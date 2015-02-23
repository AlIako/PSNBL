#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include "LifeBar.h"

class Interface
{
public:
    Interface();
    void ini();
    void draw();
    void drawScreenEffect(std::string path);
    void update(double functionTime);
    void setTarget(Player* p) {m_target=p;}
private:
    Player* m_target;
    LifeBar m_lifebar;
};


#endif // INTERFACE_H_INCLUDED
