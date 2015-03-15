#ifndef MENUSTART_H_INCLUDED
#define MENUSTART_H_INCLUDED
#include "Button.h"
#include <vector>

void menuStart(vector<Button>* b)
{
    //buttons
    b->clear();

    GTexture::getInstance()->addTexture("../data/textures/interface/title_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/box_large.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/button_large.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/button_small.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/input_large.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/blackbox.png");
    //start
    /*GTexture::getInstance()->addTexture("../data/textures/interface/title_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/single_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/multi_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/editor_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/options_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/quit_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/back_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/linkocraftcom_hq.png");

    GTexture::getInstance()->addTexture("../data/textures/interface/single_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/multi_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/editor_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/options_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/quit_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/back_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/linkocraftcom_hover_hq.png");

    //options
    GTexture::getInstance()->addTexture("../data/textures/interface/video_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/audio_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/music_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/sound_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/fullscreen_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/resolution_hq.png");

    GTexture::getInstance()->addTexture("../data/textures/interface/video_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/audio_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/music_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/sound_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/fullscreen_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/resolution_hover_hq.png");

    //multiplayer
    GTexture::getInstance()->addTexture("../data/textures/interface/host_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/joingame_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/join_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/name_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/ip_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/port_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/create_hq.png");

    GTexture::getInstance()->addTexture("../data/textures/interface/host_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/joingame_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/join_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/name_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/ip_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/port_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/create_hover_hq.png");

    //input
    GTexture::getInstance()->addTexture("../data/textures/interface/inputname_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/input_ip_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/input_port_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/ok_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/paste_hq.png");

    GTexture::getInstance()->addTexture("../data/textures/interface/ok_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/paste_hover_hq.png");

    //editor
    GTexture::getInstance()->addTexture("../data/textures/interface/new_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/open_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/test_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/delete_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/sure_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/yes_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/no_hq.png");

    GTexture::getInstance()->addTexture("../data/textures/interface/new_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/open_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/test_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/delete_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/yes_hover_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/no_hover_hq.png");

    GTexture::getInstance()->addTexture("../data/textures/interface/error_hq.png");*/

    GTexture::getInstance()->addTexture("../data/textures/interface/button_large.png");

    unsigned int ind=b->size();
    b->push_back(Button());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/title_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.6,0));
    (*b)[ind].setSize(Vector3D(0.5,0.4,0));
    (*b)[ind].setClicable(false);
    (*b)[ind].setName("title");

    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setPos(Vector3D(0.25,0.5,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("single");
    (*b)[ind].addText("Singleplayer");
    (*b)[ind].ini();

    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setPos(Vector3D(0.25,0.4,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("multi");
    (*b)[ind].addText("Multiplayer");
    (*b)[ind].ini();

    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setPos(Vector3D(0.25,0.3,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("editor");
    (*b)[ind].addText("Editor");
    (*b)[ind].ini();

    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setPos(Vector3D(0.25,0.2,0));
    (*b)[ind].setSize(Vector3D(0.5,0.075,0));
    (*b)[ind].setName("options");
    (*b)[ind].addText("Options");
    (*b)[ind].ini();

    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setPos(Vector3D(0.04,0.04,0));
    (*b)[ind].setSize(Vector3D(0.3,0.03,0));
    (*b)[ind].setName("linkocraftcom");
    (*b)[ind].addText("www.linkocraft.com");
    (*b)[ind].ini();
    (*b)[ind].setTexture(NULL);
    (*b)[ind].centerText(false);

    ind=(*b).size();
    (*b).push_back(Button());
    (*b)[ind].setPos(Vector3D(0.76,0.04,0));
    (*b)[ind].setSize(Vector3D(0.2,0.075,0));
    (*b)[ind].setName("quit");
    (*b)[ind].addText("Quit");
    (*b)[ind].ini();
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_small.png"));
}



#endif // MENUSTART_H_INCLUDED
