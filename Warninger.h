#ifndef WARNINGER_H_INCLUDED
#define WARNINGER_H_INCLUDED
#include "Block.h"

class Warninger: public Block
{
    public:
    Warninger();

    virtual void ini();
    virtual void draw();

    virtual void action(int type, Object* o=NULL);

    virtual string writeObj();
    virtual void readObj(ifstream* fichier1);

    protected:
    string m_warningType;
};


#endif // WARNINGER_H_INCLUDED
