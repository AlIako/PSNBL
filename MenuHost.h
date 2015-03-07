#ifndef MENUHOST_H_INCLUDED
#define MENUHOST_H_INCLUDED
#include "Object2D.h"
#include <vector>

void menuHost(vector<Object2D>* b)
{
    b->clear();

    unsigned int ind=b->size();
    b->push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/title_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.6,0));
    (*b)[ind].setSize(Vector3D(0.5,0.4,0));
    (*b)[ind].setName("title");
}



#endif // MENUHOST_H_INCLUDED
