#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "Game.h"
#include "Editor.h"
#include "Button.h"

class Menu
{
public:
    Menu();
    void ini();
    void play();
    void draw();
    void drawLoading();
    void updateTimes();

    string inputString(string txt,string msg,bool onlyInt=false);
    bool messageSure();
    void messageError(string msg);

    void clicOn(string name, bool leftClic);

    string command;

    private:
        SDL_Event event;

        Video* m_video;

        bool playLoop;
        bool fadingToLeave;

        double lastCursorX;
        double lastCursorY;


        Object2D m_bg;
        Object2D m_loading;
        vector<Button> m_buttons;


        GTime since_last_frame;
        double ft;//function time

        string curMenu;

        string mapSelected;
};

#endif // MENU_H_INCLUDED
