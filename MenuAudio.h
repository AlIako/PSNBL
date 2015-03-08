#ifndef MENUAUDIO_H_INCLUDED
#define MENUAUDIO_H_INCLUDED
#include "Object2D.h"
#include <vector>

void menuAudio(vector<Object2D>* b,freetype::font_data* font)
{
    b->clear();

    unsigned int ind=b->size();
    b->push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/title_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.6,0));
    (*b)[ind].setSize(Vector3D(0.5,0.4,0));
    (*b)[ind].setName("title");



    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/music_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/music_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.5,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("music");
    (*b)[ind].setClicable(true);

    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setPos(Vector3D(0.77,0.525,0));
    if(Config::getInstance()->music)
        (*b)[ind].addText("on",font);
    else
        (*b)[ind].addText("off",font);
    (*b)[ind].setName("musicon");

    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/sound_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/sound_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.4,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("sound");
    (*b)[ind].setClicable(true);

    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setPos(Vector3D(0.77,0.425,0));

    if(Config::getInstance()->sound)
        (*b)[ind].addText("on",font);
    else
        (*b)[ind].addText("off",font);

    (*b)[ind].setName("soundon");



    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/linkocraftcom_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/linkocraftcom_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.04,0.04,0));
    (*b)[ind].setSize(Vector3D(0.3,0.03,0));
    (*b)[ind].setName("linkocraftcom");
    (*b)[ind].setClicable(true);

    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/back_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/back_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.76,0.04,0));
    (*b)[ind].setSize(Vector3D(0.2,0.075,0));
    (*b)[ind].setName("back");
    (*b)[ind].setClicable(true);
}



#endif // MENUAUDIO_H_INCLUDED
