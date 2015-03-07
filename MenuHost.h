#ifndef MENUHOST_H_INCLUDED
#define MENUHOST_H_INCLUDED
#include "Object2D.h"
#include <vector>

void menuHost(vector<Object2D>* b,freetype::font_data* font)
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
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/port_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/port_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.5,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("port");

    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setPos(Vector3D(0.77,0.525,0));

    std::stringstream ss;
    ss << Config::getInstance()->port;
    (*b)[ind].addText(ss.str(),font);
    (*b)[ind].setName("porttxt");


    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/create_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/create_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.4,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("create");





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



#endif // MENUHOST_H_INCLUDED
