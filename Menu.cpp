#include "Menu.h"
#include "MenuOptions.h"
#include "MenuStart.h"
#include "MenuMultiplayer.h"
#include "MenuHost.h"
#include "MenuJoin.h"
#include "MenuServers.h"
#include "MenuEditor.h"
#include "MenuAudio.h"
#include "MenuVideo.h"

Menu::Menu()
{

}


void Menu::ini()
{
    m_video=Video::getInstance();

    string txtPath="../data/textures/interface/bg_"+Video::getInstance()->getStrHD()+".jpg";
    GTexture::getInstance()->addTexture(txtPath);
    m_bg.setTexture(GTexture::getInstance()->getTexture(txtPath));
    m_bg.setPos(Vector3D(0,0,0));
    m_bg.setSize(Vector3D(1,1,0));

    curMenu="start";
    menuStart(&m_buttons);

    SDL_ShowCursor(SDL_ENABLE);//curseur
    SDL_WM_GrabInput(SDL_GRAB_OFF);
}


void Menu::play()
{
    SDL_Event event;

    playLoop=true;

    while (playLoop)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                playLoop = false;
                break;

                case SDL_MOUSEMOTION:
                    for(unsigned int i=0;i<m_buttons.size();i++)
                    {
                        m_buttons[i].updateCursor(Vector3D(event.button.x,event.button.y,0));
                    }
                break;

                case SDL_MOUSEBUTTONUP:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    for(unsigned int i=0;i<m_buttons.size();i++)
                    {
                        if(m_buttons[i].clic(Vector3D(event.button.x,event.button.y,0)))
                        {
                            clicOn(m_buttons[i].getName());
                            break;
                        }
                    }
                }
                if(event.button.button==SDL_BUTTON_RIGHT)
                {
                }
                break;

                case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_KP_ENTER:
                    break;
                    case SDLK_RETURN:
                    break;
                    case SDLK_SPACE:
                    break;
                    default:
                    break;
                }
                break;

                case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_KP_ENTER:
                    break;
                    case SDLK_RETURN:
                    break;
                    case SDLK_ESCAPE:
                        clicOn("back");
                    break;
                    default:
                    break;
                }
                break;
            }
        }

        //update stuff
        updateTimes();
        //m_online->update();

        m_video->update(ft);

        m_bg.update(ft);
        for(unsigned int i=0;i<m_buttons.size();i++)
            m_buttons[i].update(ft);


        draw();

        SDL_Delay(10);
    }
}



void Menu::draw()
{
    m_video->beforeDraw();

    gluLookAt(5,2,1,
    1,2,0,
    0,0,1);

    //bg
    m_bg.draw();


    //buttons
    for(unsigned int i=0;i<m_buttons.size();i++)
        m_buttons[i].draw();

    m_video->afterDraw();
}

void Menu::clicOn(string name)
{
    if(name=="start")
    {
        curMenu="start";
        menuStart(&m_buttons);
    }
    if(name=="single")
    {
        game.play();
        SDL_ShowCursor(SDL_ENABLE);//curseur
        SDL_WM_GrabInput(SDL_GRAB_OFF);
    }
    if(name=="multi")
    {
        curMenu=name;
        menuMultiplayer(&m_buttons);
    }
    if(name=="editor")
    {
        curMenu=name;
        menuEditor(&m_buttons);
    }

    if(name=="options")
    {
        curMenu=name;
        menuOptions(&m_buttons);
    }
    if(name=="audio")
    {
        curMenu=name;
        menuAudio(&m_buttons);
    }
    if(name=="video")
    {
        curMenu=name;
        menuVideo(&m_buttons);
    }

    if(name=="host")
    {
        curMenu=name;
        menuHost(&m_buttons);
    }
    if(name=="join")
    {
        curMenu=name;
        menuJoin(&m_buttons);
    }
    if(name=="servers")
    {
        curMenu=name;
        menuServers(&m_buttons);
    }

    if(name=="back")
    {
        if(curMenu=="video" || curMenu=="audio")
        {
            curMenu="options";
            menuOptions(&m_buttons);
        }
        else if(curMenu=="start")
        {
            playLoop=false;
        }
        else
        {
            curMenu="start";
            menuStart(&m_buttons);
        }
    }



    if(name=="quit")
    {
        playLoop=false;
    }
    if(name=="linkocraftcom")
    {
        char url[255]="www.linkocraft.com";
        ShellExecute(NULL, "open", url,NULL, NULL, SW_SHOWNORMAL);
    }
}



void Menu::updateTimes()
{
    since_last_frame.couler();
    int timePast=since_last_frame.timePast();
    ft=timePast/15.000;//facteur temps(déplacement en fonction du temps)
    if(ft>1)
        ft=1;
    else if(ft<-1)
        ft=-1;

    since_last_frame.reset();
}


