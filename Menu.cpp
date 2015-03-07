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

    command="quit";

    m_video=Video::getInstance();

    //sound
    Gsounds::getInstance()->ini();
    Gsounds::getInstance()->loads();

    Gsounds::getInstance()->addMusic("../data/music/menu_theme.mp3");
    Gsounds::getInstance()->play("../data/music/menu_theme.mp3");


    m_font.init("../data/fonts/arial.TTF", 16);


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
                    lastCursorX=event.button.x;
                    lastCursorY=event.button.y;
                    for(unsigned int i=0;i<m_buttons.size();i++)
                        m_buttons[i].updateCursor(Vector3D(event.button.x,event.button.y,0));
                break;

                case SDL_MOUSEBUTTONUP:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    for(unsigned int i=0;i<m_buttons.size();i++)
                    {
                        if(m_buttons[i].clic(Vector3D(event.button.x,event.button.y,0)))
                        {
                            clicOn(m_buttons[i].getName(),true);
                            break;
                        }
                    }
                }
                if(event.button.button==SDL_BUTTON_RIGHT)
                {
                    for(unsigned int i=0;i<m_buttons.size();i++)
                    {
                        if(m_buttons[i].clic(Vector3D(event.button.x,event.button.y,0)))
                        {
                            clicOn(m_buttons[i].getName(),false);
                            break;
                        }
                    }
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
                        clicOn("back",true);
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

    Gsounds::getInstance()->freeAll();
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

void Menu::clicOn(string name, bool leftClic)
{
    if(leftClic && name=="start")
    {
        curMenu="start";
        menuStart(&m_buttons);
    }
    if(leftClic && name=="single")
    {
        Config::getInstance()->mode="server";
        command="play";
        playLoop=false;
    }
    if(leftClic && name=="join")
    {
        Config::getInstance()->mode="client";
        command="play";
        playLoop=false;
    }
    if(leftClic && name=="create")
    {
        Config::getInstance()->mode="server";
        command="play";
        playLoop=false;
    }
    if(leftClic && name=="multi")
    {
        curMenu=name;
        menuMultiplayer(&m_buttons,&m_font);
    }
    if(leftClic && name=="editor")
    {
        curMenu=name;
        menuEditor(&m_buttons);
    }

    if(leftClic && name=="options")
    {
        curMenu=name;
        menuOptions(&m_buttons);
    }
    if(leftClic && name=="audio")
    {
        curMenu=name;
        menuAudio(&m_buttons,&m_font);
    }
    if(leftClic && name=="sound")
    {
        Config::getInstance()->toggleSound();
        Config::getInstance()->save();
        Gsounds::getInstance()->on=Config::getInstance()->sound;
        Gsounds::getInstance()->pauseSounds(Gsounds::getInstance()->on);
        menuAudio(&m_buttons,&m_font);
    }
    if(leftClic && name=="music")
    {
        Config::getInstance()->toggleMusic();
        Config::getInstance()->save();
        Gsounds::getInstance()->music=Config::getInstance()->music;
        Gsounds::getInstance()->pauseMusic(Gsounds::getInstance()->music);
        menuAudio(&m_buttons,&m_font);
    }
    if(leftClic && name=="video")
    {
        curMenu=name;
        menuVideo(&m_buttons,&m_font);
    }
    if(leftClic && name=="fullscreen")
    {
        Config::getInstance()->toggleFullscreen();
        Config::getInstance()->save();
        menuVideo(&m_buttons,&m_font);
    }
    if(name=="resolution")
    {
        Vector3D next=Vector3D(0,0,0);
        if(leftClic)
            next=Video::getInstance()->nextResolution(Config::getInstance()->width,Config::getInstance()->height);
        else next=Video::getInstance()->previousResolution(Config::getInstance()->width,Config::getInstance()->height);

        Config::getInstance()->width=next.X;
        Config::getInstance()->height=next.Y;
        Config::getInstance()->save();
        menuVideo(&m_buttons,&m_font);
    }

    if(leftClic && name=="host")
    {
        curMenu=name;
        menuHost(&m_buttons,&m_font);
    }
    if(leftClic && name=="joingame")
    {
        curMenu=name;
        menuJoin(&m_buttons,&m_font);
    }
    if(leftClic && name=="name")
    {
        Config::getInstance()->name=inputString(Config::getInstance()->name,"../data/textures/interface/inputname_hq.png");
        Config::getInstance()->save();
        menuMultiplayer(&m_buttons,&m_font);
    }
    if(leftClic && name=="ip")
    {
        Config::getInstance()->ip=inputString(Config::getInstance()->ip,"../data/textures/interface/input_ip_hq.png");
        Config::getInstance()->save();
        menuJoin(&m_buttons,&m_font);
    }
    if(leftClic && name=="port")
    {

        std::stringstream ss;
        ss << Config::getInstance()->port;

        istringstream buffer(inputString(ss.str(),"../data/textures/interface/input_ip_hq.png",true));
        int value;
        buffer >> value;

        Config::getInstance()->port=value;
        Config::getInstance()->save();


        if(curMenu=="joingame")
            menuJoin(&m_buttons,&m_font);
        else if(curMenu=="host")
            menuHost(&m_buttons,&m_font);
    }
    if(leftClic && name=="servers")
    {
        curMenu=name;
        menuServers(&m_buttons);
    }

    if(leftClic && name=="back")
    {
        command="quit";
        if(curMenu=="video" || curMenu=="audio")
        {
            curMenu="options";
            menuOptions(&m_buttons);
        }
        else if(curMenu=="host" || curMenu=="joingame")
        {
            curMenu="multi";
            menuMultiplayer(&m_buttons,&m_font);
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



    if(leftClic && name=="quit")
    {
        playLoop=false;
    }
    if(leftClic && name=="linkocraftcom")
    {
        char url[255]="www.linkocraft.com";
        ShellExecute(NULL, "open", url,NULL, NULL, SW_SHOWNORMAL);
    }



    for(unsigned int i=0;i<m_buttons.size();i++)
        m_buttons[i].updateCursor(Vector3D(lastCursorX,lastCursorY,0));

    Gsounds::getInstance()->play("../data/sounds/hover.mp3");
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

std::string GetClipboardText()
{
    // Try opening the clipboard
    if (! OpenClipboard(NULL))
        return "";

    // Get handle of clipboard object for ANSI text
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == NULL)
        return "";

    // Lock the handle to get the actual text pointer
    char * pszText = static_cast<char*>( GlobalLock(hData) );
    if (pszText == NULL)
        return "";

    // Save text in a string class instance
    std::string text( pszText );

    // Release the lock
    GlobalUnlock( hData );

    // Release the clipboard
    CloseClipboard();

    return text;
}
string Menu::inputString(string txt,string pathTxt,bool onlyInt)
{
    string savetxt=txt;
    vector<Object2D> b;
    b.clear();
    unsigned int ind=b.size();
    b.push_back(Object2D());
    b[ind].setTexture(GTexture::getInstance()->getTexture(pathTxt));
    b[ind].setPos(Vector3D(0.25,0.15,0));
    b[ind].setSize(Vector3D(0.5,0.6,0));
    b[ind].setName("inputtext");

    ind=b.size();
    b.push_back(Object2D());
    b[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/paste_hq.png"));
    b[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/paste_hover_hq.png"));
    b[ind].setPos(Vector3D(0.28,0.3,0));
    b[ind].setSize(Vector3D(0.175,0.075,0));
    b[ind].setName("paste");

    ind=b.size();
    b.push_back(Object2D());
    b[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/ok_hq.png"));
    b[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/ok_hover_hq.png"));
    b[ind].setPos(Vector3D(0.54,0.3,0));
    b[ind].setSize(Vector3D(0.175,0.075,0));
    b[ind].setName("ok");

    ind=b.size();
    b.push_back(Object2D());
    b[ind].setPos(Vector3D(0.3,0.43,0));
    b[ind].addText(txt,&m_font);
    b[ind].setName("txt");

    bool addChar=false;
    SDL_EnableUNICODE( SDL_ENABLE );

    GTime bar_time;
    bool displayBar=true;

    bool loop=true;
    while (loop)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                loop = false;
                playLoop = false;
                break;

                case SDL_MOUSEMOTION:
                    lastCursorX=event.button.x;
                    lastCursorY=event.button.y;
                    for(unsigned int i=0;i<b.size();i++)
                        b[i].updateCursor(Vector3D(event.button.x,event.button.y,0));
                break;

                case SDL_MOUSEBUTTONUP:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    for(unsigned int i=0;i<b.size();i++)
                    {
                        if(b[i].clic(Vector3D(event.button.x,event.button.y,0)))
                        {

                            //clicOn(b[i].getName(),true);
                            if(b[i].getName()=="paste")
                            {
                                Gsounds::getInstance()->play("../data/sounds/hover.mp3");

                                string clipboard=GetClipboardText();

                                if(clipboard!="")
                                    txt=clipboard;
                                //cerr<<"clipboard: "<<txt<<endl;
                                b[ind].setText(txt);
                                break;
                            }
                            else if(b[i].getName()=="ok")
                            {
                                Gsounds::getInstance()->play("../data/sounds/hover.mp3");
                                loop=false;
                                break;
                            }
                        }
                    }
                }
                if(event.button.button==SDL_BUTTON_RIGHT)
                {
                    for(unsigned int i=0;i<b.size();i++)
                    {
                        if(b[i].clic(Vector3D(event.button.x,event.button.y,0)))
                        {
                            //clicOn(b[i].getName(),false);
                            break;
                        }
                    }
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
                    case SDLK_BACKSPACE:
                        txt=txt.substr(0,txt.size()-1);
                        b[ind].setText(txt);
                    break;
                    default:
                    break;
                }
                addChar=false;
                if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
                    addChar=true;
                if(!onlyInt)
                {
                    if( event.key.keysym.unicode == (Uint16)' ' )
                        addChar=true;
                    else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
                        addChar=true;
                    else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
                        addChar=true;
                    else if( ( event.key.keysym.unicode >= (Uint16)':' ) && ( event.key.keysym.unicode <= (Uint16)'@' ) )
                        addChar=true;
                    else if( ( event.key.keysym.unicode >= (Uint16)'[' ) && ( event.key.keysym.unicode <= (Uint16)'_' ) )
                        addChar=true;
                    else if( ( event.key.keysym.unicode >= (Uint16)'!' ) && ( event.key.keysym.unicode <= (Uint16)'/' ) )
                        addChar=true;
                }
                if(addChar)
                {
                    std::stringstream ss;
                    ss << txt<< (char)event.key.keysym.unicode;
                    txt= ss.str();
                    b[ind].setText(txt);

                    cerr<<"add char "<< txt<<endl;
                }
                break;

                case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_KP_ENTER:
                    break;
                    case SDLK_RETURN:
                        loop=false;
                    break;
                    case SDLK_ESCAPE:
                        loop=false;
                        txt=savetxt;
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


        bar_time.couler();
        if(bar_time.ecouler(500))
        {
            bar_time.reset();
            if(displayBar)
                displayBar=false;
            else displayBar=true;
        }
        if(displayBar)
            b[ind].setText(txt+"|");
        else b[ind].setText(txt);

        m_video->beforeDraw();

        gluLookAt(5,2,1,
        1,2,0,
        0,0,1);

        //bg
        m_bg.draw();


        //buttons
        for(unsigned int i=0;i<m_buttons.size();i++)
            m_buttons[i].draw();
        //b
        for(unsigned int i=0;i<b.size();i++)
            b[i].draw();

        m_video->afterDraw();

        SDL_Delay(10);
    }

    SDL_EnableUNICODE( SDL_DISABLE );

    return txt;
}





