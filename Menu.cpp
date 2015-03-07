#include "Menu.h"

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

    //buttons
    m_buttons.clear();

    GTexture::getInstance()->addTexture("../data/textures/interface/title_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/single_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/multi_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/editor_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/options_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/quit_hq.png");
    GTexture::getInstance()->addTexture("../data/textures/interface/linkocraftcom_hq.png");

    unsigned int ind=m_buttons.size();
    m_buttons.push_back(Object2D());
    m_buttons[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/title_hq.png"));
    m_buttons[ind].setPos(Vector3D(0.25,0.6,0));
    m_buttons[ind].setSize(Vector3D(0.5,0.4,0));
    m_buttons[ind].setName("title");

    ind=m_buttons.size();
    m_buttons.push_back(Object2D());
    m_buttons[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/single_hq.png"));
    m_buttons[ind].setPos(Vector3D(0.25,0.5,0));
    m_buttons[ind].setSize(Vector3D(0.5,0.075,0));
    m_buttons[ind].setName("single");

    ind=m_buttons.size();
    m_buttons.push_back(Object2D());
    m_buttons[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/multi_hq.png"));
    m_buttons[ind].setPos(Vector3D(0.25,0.4,0));
    m_buttons[ind].setSize(Vector3D(0.5,0.075,0));
    m_buttons[ind].setName("multi");

    ind=m_buttons.size();
    m_buttons.push_back(Object2D());
    m_buttons[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/editor_hq.png"));
    m_buttons[ind].setPos(Vector3D(0.25,0.3,0));
    m_buttons[ind].setSize(Vector3D(0.5,0.075,0));
    m_buttons[ind].setName("editor");

    ind=m_buttons.size();
    m_buttons.push_back(Object2D());
    m_buttons[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/options_hq.png"));
    m_buttons[ind].setPos(Vector3D(0.25,0.2,0));
    m_buttons[ind].setSize(Vector3D(0.5,0.075,0));
    m_buttons[ind].setName("options");

    ind=m_buttons.size();
    m_buttons.push_back(Object2D());
    m_buttons[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/linkocraftcom_hq.png"));
    m_buttons[ind].setPos(Vector3D(0.04,0.04,0));
    m_buttons[ind].setSize(Vector3D(0.3,0.03,0));
    m_buttons[ind].setName("linkocraftcom");

    ind=m_buttons.size();
    m_buttons.push_back(Object2D());
    m_buttons[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/quit_hq.png"));
    m_buttons[ind].setPos(Vector3D(0.76,0.04,0));
    m_buttons[ind].setSize(Vector3D(0.2,0.075,0));
    m_buttons[ind].setName("quit");


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
                            clicOn(m_buttons[i].getName());
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
                    playLoop = false;
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
    if(name=="single")
    {
        game.play();
        SDL_ShowCursor(SDL_ENABLE);//curseur
        SDL_WM_GrabInput(SDL_GRAB_OFF);
    }
    if(name=="multi")
    {
        game.play();
        SDL_ShowCursor(SDL_ENABLE);//curseur
        SDL_WM_GrabInput(SDL_GRAB_OFF);
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


