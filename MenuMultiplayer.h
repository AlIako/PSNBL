#ifndef MENUMULTIPLAYER_H_INCLUDED
#define MENUMULTIPLAYER_H_INCLUDED
#include "Object2D.h"
#include <vector>

void menuMultiplayer(vector<Button>* b,freetype::font_data* font)
{
    b->clear();

    unsigned int ind=b->size();
    (*b).push_back(Button());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/title_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.6,0));
    (*b)[ind].setSize(Vector3D(0.5,0.4,0));
    (*b)[ind].setName("title");
    (*b)[ind].ini();



    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_large.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.5,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("name");
    (*b)[ind].setClicable(true);
    (*b)[ind].ini();

    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_large.png"));
    (*b)[ind].setPos(Vector3D(0.77,0.525,0));
    (*b)[ind].addText(Config::getInstance()->name,font);
    (*b)[ind].setName("nametxt");
    (*b)[ind].ini();

    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_large.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.4,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("host");
    (*b)[ind].setClicable(true);
    (*b)[ind].ini();

    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_large.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.3,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("joingame");
    (*b)[ind].setClicable(true);
    (*b)[ind].ini();


    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_large.png"));
    (*b)[ind].setPos(Vector3D(0.04,0.04,0));
    (*b)[ind].setSize(Vector3D(0.3,0.03,0));
    (*b)[ind].setName("linkocraftcom");
    (*b)[ind].setClicable(true);
    (*b)[ind].ini();

    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_large.png"));
    (*b)[ind].setPos(Vector3D(0.76,0.04,0));
    (*b)[ind].setSize(Vector3D(0.2,0.075,0));
    (*b)[ind].setName("back");
    (*b)[ind].setClicable(true);
    (*b)[ind].ini();
}



#endif // MENUMULTIPLAYER_H_INCLUDED
