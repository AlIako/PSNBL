#include "Menu.h"


/*
//template
template <typename T>
T myMax(T left, T right)
{
    return (left > right) ? left : right;
}
double bigger = myMax<double> (3.45,2.34);*/

int main ( int argc, char** argv )
{

    cerr<<"Start main"<<endl;
    srand (time(NULL));

    Config::getInstance()->load();

    Video* m_video=Video::getInstance();
    m_video->ini();

    TextManager::getInstance()->ini();


    Menu menu;

    string nextCommand="play";

    while(nextCommand!="quit")
    {
        menu.ini();
        menu.play();
        nextCommand=menu.command;

        if(nextCommand.find("play")!=string::npos)
        {
            Game game;
            //game.play();
            if(nextCommand.size()>5)
                game.play(nextCommand.substr(5,nextCommand.size()));
            else
                game.play();
        }
        else if(nextCommand.find("editor")!=string::npos)
        {
            Editor Editor;
            Editor.play(nextCommand.substr(7,nextCommand.size()));
        }
    }

   /* bool playGame=true;
    //playGame=false;

    if(playGame)
    {
        Game game;
        game.play();
    }
    else
    {
        Editor Editor;
        Editor.play();
    }*/

    Gsounds::getInstance()->close();
    m_video->close();

    return 0;
}
