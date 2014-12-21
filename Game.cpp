#include "Game.h"

Game::Game()
{

}

void Game::ini()
{
    m_video.ini();

    playerList.push_back(new Personnage());
    playerList.push_back(new Personnage());


    m_online.playerList=&playerList;
    m_online.ini();
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

                case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_LEFT:
                    playerList[0]->pressKey(LEFT,true);
                    break;
                    case SDLK_RIGHT:
                    playerList[0]->pressKey(RIGHT,true);
                    break;
                    case SDLK_UP:
                    playerList[0]->pressKey(UP,true);
                    break;
                    case SDLK_DOWN:
                    playerList[0]->pressKey(DOWN,true);
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
                    case SDLK_LEFT:
                    playerList[0]->pressKey(LEFT,false);
                    break;
                    case SDLK_RIGHT:
                    playerList[0]->pressKey(RIGHT,false);
                    break;
                    case SDLK_UP:
                    playerList[0]->pressKey(UP,false);
                    break;
                    case SDLK_DOWN:
                    playerList[0]->pressKey(DOWN,false);
                    break;
                    default:
                    break;
                }
                break;
            }
        }

        updateMultiplayer();
        m_online.update();

        playerList[0]->handlePressedKeys();

        //draw
        m_video.beforeDraw();

        for(unsigned int i=0;i<playerList.size();i++)
        {
            playerList[i]->draw();
        }


        m_video.afterDraw();

        SDL_Delay(60);
    }


    close();
}



void Game::updateMultiplayer()
{
    infosSocket s;

    //send

    //send player position and angle
    s.type=1;
    s.variable[0]=playerList[0]->getX();
    s.variable[1]=playerList[0]->getY();
    s.variable[2]=playerList[0]->getAngle();

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
                playerList[1]->setPos(s.variable[0],s.variable[1]);
                playerList[1]->setAngle(s.variable[2]);
            }
        }
    }
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




