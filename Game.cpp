#include "Game.h"

Game::Game()
{

}

void Game::ini()
{
    m_video.ini();

    unsigned int ind=playerList.size();
    playerList.push_back(new Player());
    playerList[ind]->gtext=gtext;
    playerList[ind]->ini();

    ind=playerList.size();
    playerList.push_back(new Player());
    playerList[ind]->gtext=gtext;
    playerList[ind]->ini();

    m_online.ini();

    m_map.gtext=gtext;
    m_map.ini();
    m_map.playerList=&playerList;

    m_camera.setCible(playerList[0]);

    grabCursor=true;
}

void Game::play()
{
    ini();
    //SDL_EnableKeyRepeat(10, 0);
    playLoop=true;
    while (playLoop)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                playLoop = false;
                break;

                case SDL_MOUSEMOTION:
                m_camera.onMouseMotion(event.motion);
                break;

                case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_a:
                    playerList[0]->pressKey(LEFT,true);
                    break;
                    case SDLK_d:
                    playerList[0]->pressKey(RIGHT,true);
                    break;
                    case SDLK_w:
                    playerList[0]->pressKey(UP,true);
                    break;
                    case SDLK_s:
                    playerList[0]->pressKey(DOWN,true);
                    break;
                    case SDLK_SPACE:
                    //jump
                    playerList[0]->setVel(Vector3D(playerList[0]->getVel().X,playerList[0]->getVel().Y,0.4));
                    break;
                    case SDLK_ESCAPE:
                    playLoop = false;
                    break;
                    default:
                    break;
                }
                break;

                case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_a:
                    playerList[0]->pressKey(LEFT,false);
                    break;
                    case SDLK_d:
                    playerList[0]->pressKey(RIGHT,false);
                    break;
                    case SDLK_w:
                    playerList[0]->pressKey(UP,false);
                    break;
                    case SDLK_s:
                    playerList[0]->pressKey(DOWN,false);
                    break;
                    case SDLK_c:
                    if(grabCursor)
                    {
                        SDL_ShowCursor(SDL_ENABLE);//pas de curseur
                        SDL_WM_GrabInput(SDL_GRAB_OFF);
                        grabCursor=false;
                    }
                    else
                    {
                        SDL_ShowCursor(SDL_DISABLE);//pas de curseur
                        SDL_WM_GrabInput(SDL_GRAB_ON);
                        grabCursor=true;
                    }
                    break;
                    default:
                    break;
                }
                break;
            }
        }
        //update stuff
        updateTimes();
        updateMultiplayer();
        m_online.update();

        m_map.update(ft);


        //draw
        m_video.beforeDraw();

        m_camera.look();



        for(unsigned int i=1, count=playerList.size();i<count;i++)
            playerList[i]->draw();

        m_map.draw();


        m_video.afterDraw();

        SDL_Delay(10);
    }


    close();
}



void Game::updateMultiplayer()
{
    infosSocket s;

    //send

    //send player position and angle
    s.type=1;

    s.variable[0]=playerList[0]->getPos().X;
    s.variable[1]=playerList[0]->getPos().Y;
    s.variable[2]=playerList[0]->getPos().Z;
    s.variable[3]=playerList[0]->getRot().Z;

    m_online.sendSocketReplace(s);//add socket to queue


    //receive
    for(int i = 0;i<RECEIVE_SOCKET_HANDLE_PER_FRAME;i++)
    {
        s=m_online.getNextSocketRemove();//get next socket on the queue
        if(s.type!=-1)//if something on the list
        {
            //player position and angle
            if(s.type==1)
            {
                playerList[1]->setPos(Vector3D(s.variable[0],s.variable[1],s.variable[2]));
                playerList[1]->setRot(Vector3D(0,0,s.variable[3]));
            }
        }
    }
}




void Game::updateTimes()
{
    since_last_frame.couler();
    int timePast=since_last_frame.timePast();
    ft=timePast/15.000;//facteur temps(déplacement en fonction du temps)
    if(ft>1)
        ft=1;
    else if(ft<-1)
        ft=-1;

    m_camera.updateTime(ft);

    since_last_frame.reset();
}









void Game::close()
{
    m_online.close();
    m_video.close();

    cerr<<"Exited cleanly.";
}


Game::~Game()
{

}




