#ifndef FADER_H_INCLUDED
#define FADER_H_INCLUDED
#include "Block.h"

class Fader: public Block
{
    public:
    Fader();

    virtual void ini();
    virtual void draw();

    virtual void action(int type, Object* o=NULL);

    virtual string writeObj();
    virtual void readObj(ifstream* fichier1);

    protected:
    double m_r;
    double m_g;
    double m_b;

    bool m_fadeIn;
};




#endif // FADER_H_INCLUDED
