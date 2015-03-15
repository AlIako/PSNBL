#ifndef MENUMULTIPLAYER_H_INCLUDED
#define MENUMULTIPLAYER_H_INCLUDED
#include "Object2D.h"
#include <vector>

void menuMultiplayer(vector<Button>* b)
{
    b->clear();

    unsigned int ind=b->size();
    b->push_back(Button());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/title_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.6,0));
    (*b)[ind].setSize(Vector3D(0.5,0.4,0));
    (*b)[ind].setName("title");



    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setPos(Vector3D(0.25,0.5,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("name");

    stringstream ss;
    ss<<"Name: "<<Config::getInstance()->name;
    (*b)[ind].addText(ss.str());
    (*b)[ind].ini();





    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setPos(Vector3D(0.25,0.4,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("host");
    (*b)[ind].addText("Host game");
    (*b)[ind].ini();

    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setPos(Vector3D(0.25,0.3,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("joingame");
    (*b)[ind].addText("Join game");
    (*b)[ind].ini();


    ind=(*b).size();
    b->push_back(Button());
    (*b)[ind].setPos(Vector3D(0.04,0.04,0));
    (*b)[ind].setSize(Vector3D(0.3,0.03,0));
    (*b)[ind].setName("linkocraftcom");
    (*b)[ind].addText("www.linkocraft.com");
    (*b)[ind].ini();
    (*b)[ind].centerText(false);
    (*b)[ind].setTexture(NULL);

    ind=(*b).size();
    b->push_back(Button());
    (*b)[ind].setPos(Vector3D(0.76,0.04,0));
    (*b)[ind].setSize(Vector3D(0.2,0.075,0));
    (*b)[ind].setName("back");
    (*b)[ind].addText("Back");
    (*b)[ind].ini();
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_small.png"));
}



#endif // MENUMULTIPLAYER_H_INCLUDED
