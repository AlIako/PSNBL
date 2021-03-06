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
    void draw();
    void endLevel();

    bool checkEndLevel();

    void handleCommands();
    void handleTracer();

    bool castSpell(Player* p, string spell, Vector3D param1=Vector3D(0,0,0));
    void playPlayerSound(Player* p,string sound);
    bool isMainPlayer(Player* p);

    void updateCamMode();
    void switchSpectate(int d);


    void updateMultiplayer();
    Player* playerForId(int id);

    Object* findBoss();

    void updateTimes();




    void close();

    string command;

    private:
    bool playLoop;
    bool fadingToLeave;

    Video* m_video;
    Online* m_online;
    vector<Player*> playerList;
    Camera m_camera;
    Chat m_chat;

    GTime since_last_frame;
    double ft;//function time

    SDL_Event event;
    bool grabCursor;

    std::string m_mode;//playing, death(spectate)

    int m_fps;
    GTime m_fpsTime;
    //temporary bool, needs to be done in a better way
    bool shiftPushed;


    bool alreadyDead;
    bool levelEnded;

    string pathTest;
};


#endif // GAME_H_INCLUDED
