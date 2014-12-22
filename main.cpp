#include "Game.h"

int main ( int argc, char** argv )
{
    Gtexture* gtext=new Gtexture();

    Game game;
    game.gtext=gtext;

    game.play();
    return 0;
}
