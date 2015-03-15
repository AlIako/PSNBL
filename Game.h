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
#include "Interface.h"
#include "SpellRope.h"
#include "Tracer.h"


class Game
{
    public:
    Game();

    void ini();



    void play(string path="");

    void handleCommands();
    void handleTracer();

    bool castSpell(Player* p, string spell, Vector3D param1=Vector3D(0,0,0));
    void playPlayerSound(Player* p,string sound);
    bool isMainPlayer(Player* p);

    void updateCamMode();
    void switchSpectate(int d);


    void updateMultiplayer();
    Player* playerForId(int id);

    void updateTimes();




    void close();
    ~Game();

    private:
    bool playLoop;
    bool fadingToLeave;

    Video* m_video;
    Online* m_online;
    Map m_map;
    vector<Player*> playerList;
    Camera m_camera;
    Chat m_chat;
    Interface m_interface;

    GTime since_last_frame;
    double ft;//function time

    bool grabCursor;

    std::string m_mode;//playing, death(spectate)

    int m_fps;
    GTime m_fpsTime;
    //temporary bool, needs to be done in a better way
    bool shiftPushed;


    bool alreadyDead;

    string pathTest;
};


#endif // GAME_H_INCLUDED
