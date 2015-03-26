#ifndef LIGHTER_H_INCLUDED
#define LIGHTER_H_INCLUDED
#include "Block.h"

class Lighter: public Block
{
    public:
    Lighter();

    virtual void ini();
    virtual void draw();

    virtual void action(int type, Object* o=NULL);

    virtual string writeObj();
    virtual void readObj(ifstream* fichier1);

    protected:
    double m_r;
    double m_g;
    double m_b;

    double m_alpha;
    double m_at;

    bool m_on;
};





#endif // LIGHTER_H_INCLUDED
