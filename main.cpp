#include "Game.h"

int main ( int argc, char** argv )
{
    cerr<<"Start main"<<endl;
    srand (time(NULL));


    Game game;

    game.play();
    return 0;
}
