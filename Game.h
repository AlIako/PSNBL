#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Video.h"
#include "Online.h"
#include "Map.h"

class Game
{
    public:
    Game();

    void ini();



    void play();
    void updateMultiplayer();




    void close();
    ~Game();


    //public attributes
    Gtexture* gtext;

    private:
    bool playLoop;
    Video m_video;
    Online m_online;
    Map m_map;
    vector<Personnage*> playerList;
};


#endif // GAME_H_INCLUDED
