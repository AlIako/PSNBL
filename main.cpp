#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Video.h"
#include "Online.h"

int main ( int argc, char** argv )
{
    Video m_video;
    m_video.ini();

    vector<Personnage*> playerList;
    playerList.push_back(new Personnage());
    playerList.push_back(new Personnage());


    Online m_online;
    m_online.playerList=&playerList;
    m_online.ini();



    //SDL_EnableKeyRepeat(10, 0);
    bool done=false;

    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                done = true;
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
                    done = true;
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



    m_online.close();
    m_video.close();

    cerr<<"Exited cleanly.";
    return 0;
}
