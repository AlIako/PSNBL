#ifndef MENUOPTIONS_H_INCLUDED
#define MENUOPTIONS_H_INCLUDED
#include "Object2D.h"
#include <vector>

void menuOptions(vector<Object2D>* b)
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
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/video_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/video_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.5,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("video");
    (*b)[ind].setClicable(true);

    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/audio_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/audio_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.4,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("audio");
    (*b)[ind].setClicable(true);



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


#endif // MENUOPTIONS_H_INCLUDED
