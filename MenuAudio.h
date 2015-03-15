#ifndef MENUAUDIO_H_INCLUDED
#define MENUAUDIO_H_INCLUDED
#include "Object2D.h"
#include <vector>

void menuAudio(vector<Button>* b)
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
    (*b)[ind].setName("music");

    stringstream ss;
    ss<<"Music: ";
    if(Config::getInstance()->music)
        ss<<"On";
    else ss<<"Off";

    (*b)[ind].addText(ss.str());
    (*b)[ind].ini();

    /*ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setPos(Vector3D(0.77,0.525,0));
    if(Config::getInstance()->music)
        (*b)[ind].addText("on",font);
    else
        (*b)[ind].addText("off",font);
    (*b)[ind].setName("musicon");*/

    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setPos(Vector3D(0.25,0.4,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("sound");

    stringstream ss2;
    ss2<<"Sound: ";
    if(Config::getInstance()->sound)
        ss2<<"On";
    else ss2<<"Off";
    (*b)[ind].addText(ss2.str());
    (*b)[ind].ini();

    /*ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setPos(Vector3D(0.77,0.425,0));

    if(Config::getInstance()->sound)
        (*b)[ind].addText("on",font);
    else
        (*b)[ind].addText("off",font);

    (*b)[ind].setName("soundon");*/



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



#endif // MENUAUDIO_H_INCLUDED
