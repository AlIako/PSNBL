#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "Game.h"
#include "Editor.h"
#include "Object2D.h"


class Menu
{
public:
    Menu();
    void ini();
    void play();
    void draw();
    void updateTimes();


    private:
        Video* m_video;

        bool playLoop;

        Game game;
        //Editor Editor;

        Object2D m_bg;
        vector<Object2D> m_buttons;


        GTime since_last_frame;
        double ft;//function time
};

#endif // MENU_H_INCLUDED
