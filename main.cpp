#include "Game.h"

int main ( int argc, char** argv )
{
    srand (time(NULL));

    GTexture* gtext=new GTexture();

    Game game;
    game.gtext=gtext;

    game.play();
    return 0;
}
