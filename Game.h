#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL.h>
#include <GL/glew.h>
#include "Video.h"
#include "Online.h"
#include "Map.h"
#include "Camera.h"
#include "GTime.h"
#include "Chat.h"

class Game
{
    public:
    Game();

    void ini();



    void play();

    void updateCamMode();
    void switchSpectate(int d);


    void updateMultiplayer();
    Player* playerForId(int id);

    void updateTimes();




    void close();
    ~Game();

    private:
    bool playLoop;
    Video* m_video;
    Online* m_online;
    Map m_map;
    vector<Player*> playerList;
    Camera m_camera;
    Chat m_chat;

    GTime since_last_frame;
    double ft;//function time

    bool grabCursor;

    std::string m_mode;//playing, death(spectate)
};


#endif // GAME_H_INCLUDED
