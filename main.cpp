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

    Video* m_video=Video::getInstance();
    m_video->ini();

    Menu menu;
    menu.ini();
    menu.play();

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
