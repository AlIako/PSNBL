#ifndef SPELL_H_INCLUDED
#define SPELL_H_INCLUDED
#include <string>
#include "GTime.h"
#include "Gtexture.h"
#include "Video.h"
#include "Vector3D.h"
#include "Tracer.h"

using namespace std;

class Spell
{
public:
    Spell();
    void ini();
    virtual void update(double functionTime);
    void draw();

    virtual bool cast();
    void resetCooldown();

    static int nameToId(string name);
    static string idToName(int id);

    std::string getName() {return m_name;}
protected:
    string m_required;//require energy, mana, nothing?
    string m_name;
    int m_cooldown;
    GTime m_lastCast;

    Texture* m_icon;
    Vector3D m_position;
    Vector3D m_size;
};


#endif // SPELL_H_INCLUDED
