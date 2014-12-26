#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Video.h"
#include "Online.h"
#include "Map.h"
#include "Camera.h"
#include "GTime.h"

class Game
{
    public:
    Game();

    void ini();



    void play();
    void updateMultiplayer();
    Player* playerForId(int id);

    void updateTimes();




    void close();
    ~Game();


    //public attributes
    GTexture* gtext;

    private:
    bool playLoop;
    Video m_video;
    Online m_online;
    Map m_map;
    vector<Player*> playerList;
    Camera m_camera;

    GTime since_last_frame;
    double ft;//function time

    bool grabCursor;

    bool m_incontrol;
};


#endif // GAME_H_INCLUDED
