#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Video.h"
#include "Online.h"


class Game
{
    public:
    Game();

    void ini();



    void play();
    void updateMultiplayer();




    void close();
    ~Game();

    private:
    bool playLoop;
    Video m_video;
    Online m_online;
    vector<Personnage*> playerList;
};


#endif // GAME_H_INCLUDED
