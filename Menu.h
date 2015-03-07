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

    string inputString(string txt,string pathTxt,bool onlyInt=false);

    void clicOn(string name, bool leftClic);

    string command;

    private:
        SDL_Event event;
        freetype::font_data m_font;

        Video* m_video;

        bool playLoop;

        double lastCursorX;
        double lastCursorY;


        Object2D m_bg;
        vector<Object2D> m_buttons;


        GTime since_last_frame;
        double ft;//function time

        string curMenu;
};

#endif // MENU_H_INCLUDED
