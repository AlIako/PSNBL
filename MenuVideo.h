#ifndef MENUVIDEO_H_INCLUDED
#define MENUVIDEO_H_INCLUDED
#include "Object2D.h"
#include <vector>

void menuVideo(vector<Object2D>* b)
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
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/fullscreen_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/fullscreen_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.5,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("fullscreen");

    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/resolution_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/resolution_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.4,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("resolution");



    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/linkocraftcom_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/linkocraftcom_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.04,0.04,0));
    (*b)[ind].setSize(Vector3D(0.3,0.03,0));
    (*b)[ind].setName("linkocraftcom");

    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/back_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/back_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.76,0.04,0));
    (*b)[ind].setSize(Vector3D(0.2,0.075,0));
    (*b)[ind].setName("back");
}



#endif // MENUVIDEO_H_INCLUDED
