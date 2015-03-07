#include "Menu.h"

Menu::Menu()
{

}


void Menu::ini()
{
    m_video=Video::getInstance();

    GTexture::getInstance()->addTexture("../data/textures/interface/bg.jpg");
    m_bg.setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/bg.jpg"));
    m_bg.setPos(Vector3D(0,0,0));
    m_bg.setSize(Vector3D(1,1,0));

    m_buttons.clear();

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
                break;

                case SDL_MOUSEBUTTONUP:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                }
                if(event.button.button==SDL_BUTTON_RIGHT)
                {
                    game.play();
                    SDL_ShowCursor(SDL_ENABLE);//curseur
                    SDL_WM_GrabInput(SDL_GRAB_OFF);
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

    //bg
    m_bg.draw();

    //buttons
    for(unsigned int i=0;i<m_buttons.size();i++)
        m_buttons[i].draw();


    m_video->afterDraw();
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


