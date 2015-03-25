#ifndef FOGGER_H_INCLUDED
#define FOGGER_H_INCLUDED
#include "Block.h"

class Fogger: public Block
{
    public:
    Fogger();

    virtual void ini();
    virtual void draw();

    virtual void action(int type, Object* o=NULL);

    virtual string writeObj();
    virtual void readObj(ifstream* fichier1);

    protected:
    double m_r;
    double m_g;
    double m_b;

    double m_distStart;
    double m_distEnd;
};



#endif // FOGGER_H_INCLUDED
