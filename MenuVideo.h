#ifndef MENUVIDEO_H_INCLUDED
#define MENUVIDEO_H_INCLUDED
#include "Object2D.h"
#include <vector>

void menuVideo(vector<Button>* b)
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
    (*b)[ind].setName("fullscreen");

    stringstream ss;
    ss<<"Fullscreen: ";
    if(Config::getInstance()->fullscreen)
        ss<<"On";
    else ss<<"Off";

    (*b)[ind].addText(ss.str());
    (*b)[ind].ini();




    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setPos(Vector3D(0.25,0.4,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("resolution");

    stringstream ss2;
    ss2 <<"Resolution: ";
    ss2 << Config::getInstance()->width <<" * " << Config::getInstance()->height;
    (*b)[ind].addText(ss2.str());
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



#endif // MENUVIDEO_H_INCLUDED
