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
#include "MenuSingle.h"

Menu::Menu()
{
    mapSelected="";
    command="";
}


void Menu::ini()
{
    mapSelected="";
    command="quit";

    m_video=Video::getInstance();

    //loading
    GTexture::getInstance()->addTexture("../data/textures/interface/loading.png");

    m_loading.setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/loading.png"));
    m_loading.setPos(Vector3D(0.3,0.4,0));
    m_loading.setSize(Vector3D(0.4,0.2,0));

    drawLoading();


    //sound
    Gsounds::getInstance()->ini();
    Gsounds::getInstance()->loads();

    Gsounds::getInstance()->addMusic("../data/music/menu_theme.mp3");
    Gsounds::getInstance()->play("../data/music/menu_theme.mp3");




    string txtPath="../data/textures/interface/bg_"+Video::getInstance()->getStrHD()+".jpg";
    GTexture::getInstance()->addTexture(txtPath);
    m_bg.setTexture(GTexture::getInstance()->getTexture(txtPath));
    m_bg.setPos(Vector3D(0,0,0));
    m_bg.setSize(Vector3D(1,1,0));

    curMenu="start";
    menuStart(&m_buttons);

    SDL_ShowCursor(SDL_ENABLE);//curseur
    SDL_WM_GrabInput(SDL_GRAB_OFF);



    m_video->getFade()->startFadeOut();
}


void Menu::play()
{
    mapSelected="";
    playLoop=true;
    fadingToLeave=false;

    while (playLoop)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                fadingToLeave=true;
                playLoop=false;
                command="quit";
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
                        if(m_buttons[i].getClicable() && m_buttons[i].clic(Vector3D(event.button.x,event.button.y,0)))
                        {
                            clicOn(m_buttons[i].getName(),true);
                            break;
                        }
                    }
                }
                else if(event.button.button==SDL_BUTTON_RIGHT)
                {
                    for(unsigned int i=0;i<m_buttons.size();i++)
                    {
                        if(m_buttons[i].getClicable() && m_buttons[i].clic(Vector3D(event.button.x,event.button.y,0)))
                        {
                            clicOn(m_buttons[i].getName(),false);
                            break;
                        }
                    }
                }
                else if(event.button.button==SDL_BUTTON_WHEELUP)
                {
                    if(curMenu=="editor")
                        for(unsigned int i=9;i<m_buttons.size();i++)
                        {
                            m_buttons[i].translate(0,-0.05);
                            if(m_buttons[i].getPos().Y>0.4 || m_buttons[i].getPos().Y<0.1)
                                m_buttons[i].setVisible(false);
                            else
                                m_buttons[i].setVisible(true);
                        }
                }
                else if(event.button.button==SDL_BUTTON_WHEELDOWN)
                {
                    if(curMenu=="editor")
                        for(unsigned int i=9;i<m_buttons.size();i++)
                        {
                            m_buttons[i].translate(0,0.05);
                            if(m_buttons[i].getPos().Y>0.4 || m_buttons[i].getPos().Y<0.1)
                                m_buttons[i].setVisible(false);
                            else
                                m_buttons[i].setVisible(true);
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

        SDL_Delay(20);


        if(fadingToLeave)
        {
            if(Video::getInstance()->getFade()->getFading()==false)
            {
                Video::getInstance()->getFade()->startFadeIn();
            }
            if(Video::getInstance()->getFade()->getAlpha()>=1)
            {
                playLoop=false;
                fadingToLeave=false;
            }
        }
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

    //text freetype
    //TextManager::getInstance()->display();

    //fading
    m_video->matrixOrtho2D();
    m_video->getFade()->draw();
    m_video->matrixProjection();


    m_video->afterDraw();
}

void Menu::drawLoading()
{
    //glDisable(GL_FOG);
    m_video->beforeDraw();

    gluLookAt(5,2,1,
    1,2,0,
    0,0,1);

    m_loading.draw();

    m_video->afterDraw();
    //glEnable(GL_FOG);
}


void Menu::clicOn(string name, bool leftClic)
{
    Gsounds::getInstance()->play("../data/sounds/hover.mp3");

    if(leftClic && name=="start")
    {
        curMenu="start";
        menuStart(&m_buttons);
    }
    if(leftClic && name=="single")
    {
        Config::getInstance()->mode="server";
        Online::getInstance()->setActive(false);
        command="play";

        mapSelected="";
        curMenu=name;
        menuSingle(&m_buttons);

        //fadingToLeave=true;
    }
    if(leftClic && curMenu=="single" && name!="single" && name!="linkocraftcom" && name!="back" && name!="title")
    {
        Config::getInstance()->mode="server";
        Online::getInstance()->setActive(false);
        command="play "+name;
        mapSelected=name;
        fadingToLeave=true;
    }
    if(leftClic && name=="join")
    {
        Config::getInstance()->mode="client";

        Online::getInstance()->setActive(true);
        Online::getInstance()->ini();
        Online::getInstance()->startThreads();

        if(!Online::getInstance()->m_server)
        {
            Online::getInstance()->setIncontrol(false);

            GTime start_try_connect;
            start_try_connect.reset();
            while(!Online::getInstance()->m_connectionEstablished && !start_try_connect.ecouler(2500))
            {
                start_try_connect.couler();
                Online::getInstance()->update();
                SDL_Delay(50);
            }
        }

        if(Online::getInstance()->m_connectionEstablished)
        {
            command="play";
            fadingToLeave=true;
        }
        else//fail connection
        {
            Online::getInstance()->closeOnline();
            messageError("Connection to server failed.");
        }

    }
    if(leftClic && name=="create")
    {
        Config::getInstance()->mode="server";

        Online::getInstance()->setActive(true);
        Online::getInstance()->ini();

        command="play";
        fadingToLeave=true;
    }
    if(leftClic && name=="multi")
    {
        curMenu=name;
        menuMultiplayer(&m_buttons);
    }
    if(leftClic && name=="editor")
    {
        mapSelected="";
        curMenu=name;
        menuEditor(&m_buttons,"../data/"+Config::getInstance()->editorpath+"/");
    }
    if(curMenu=="editor" && (name=="patterns" || name=="levels"))
    {
        mapSelected="";
        Config::getInstance()->editorpath=name;
        Config::getInstance()->save();
        menuEditor(&m_buttons,"../data/"+Config::getInstance()->editorpath+"/");
    }
    if(name.find("../data/patterns/")!=string::npos || name.find("../data/levels/")!=string::npos)
    {
        if(leftClic)
        {
            mapSelected=name;
            for(unsigned int i=0;i<m_buttons.size();i++)
            {
                if(m_buttons[i].getName()==name)
                    m_buttons[i].select(true);
                else m_buttons[i].select(false);
            }
        }
        else//right clic: open map with editor
        {
            command="editor "+name;
            fadingToLeave=true;
        }
    }
    if(leftClic && name=="open")
    {
        if(curMenu=="editor")
        {
            if(mapSelected!="")
            {
                command="editor "+mapSelected;
                cerr<<"going editor "<< command<<endl;
                fadingToLeave=true;
            }
        }
    }
    if(leftClic && name=="delete")
    {
        if(curMenu=="editor")
        {
            if(mapSelected!="")
            {
                if(messageSure())
                {
                    cerr<<"deleting "<< mapSelected<<endl;

                    char* tempChar=stringtochar(mapSelected);
                    remove(tempChar);
                    delete tempChar;

                    mapSelected="";

                    menuEditor(&m_buttons,"../data/"+Config::getInstance()->editorpath+"/");
                }
            }
        }
    }
    if(leftClic && name=="test")
    {
        if(curMenu=="editor")
        {
            if(mapSelected!="")
            {
                Config::getInstance()->mode="server";

                Online::getInstance()->setActive(false);

                command="play "+mapSelected;
                cerr<<"going play "<< command<<endl;
                fadingToLeave=true;
            }
        }
    }
    if(leftClic && name=="new")
    {
        if(curMenu=="editor")
        {
            string inputName=inputString("","Enter Name:");
            if(inputName!="")
            {
                inputName="../data/patterns/"+inputName+".txt";
                command="editor "+inputName;
                cerr<<"going editor "<< command<<endl;
                fadingToLeave=true;
            }
        }
    }

    if(leftClic && name=="options")
    {
        curMenu=name;
        menuOptions(&m_buttons);
    }
    if(leftClic && name=="audio")
    {
        curMenu=name;
        menuAudio(&m_buttons);
    }
    if(leftClic && name=="sound")
    {
        Config::getInstance()->toggleSound();
        Config::getInstance()->save();
        Gsounds::getInstance()->on=Config::getInstance()->sound;
        Gsounds::getInstance()->pauseSounds(Gsounds::getInstance()->on);
        menuAudio(&m_buttons);
    }
    if(leftClic && name=="music")
    {
        Config::getInstance()->toggleMusic();
        Config::getInstance()->save();
        Gsounds::getInstance()->music=Config::getInstance()->music;
        Gsounds::getInstance()->pauseMusic(Gsounds::getInstance()->music);
        menuAudio(&m_buttons);
    }
    if(leftClic && name=="video")
    {
        curMenu=name;
        menuVideo(&m_buttons);
    }
    if(leftClic && name=="fullscreen")
    {
        Config::getInstance()->toggleFullscreen();
        Config::getInstance()->save();
        menuVideo(&m_buttons);
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
        menuVideo(&m_buttons);
    }

    if(leftClic && name=="host")
    {
        curMenu=name;
        menuHost(&m_buttons);
    }
    if(leftClic && name=="joingame")
    {
        curMenu=name;
        menuJoin(&m_buttons);
    }
    if(leftClic && name=="name")
    {
        Config::getInstance()->name=inputString(Config::getInstance()->name,"Enter Name:");
        Config::getInstance()->save();
        menuMultiplayer(&m_buttons);
    }
    if(leftClic && name=="ip")
    {
        Config::getInstance()->ip=inputString(Config::getInstance()->ip,"Enter ip:");
        Config::getInstance()->save();
        menuJoin(&m_buttons);
    }
    if(leftClic && name=="port")
    {

        std::stringstream ss;
        ss << Config::getInstance()->port;

        istringstream buffer(inputString(ss.str(),"Enter Port:",true));
        int value;
        buffer >> value;

        Config::getInstance()->port=value;
        Config::getInstance()->save();


        if(curMenu=="joingame")
            menuJoin(&m_buttons);
        else if(curMenu=="host")
            menuHost(&m_buttons);
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
            menuMultiplayer(&m_buttons);
        }
        else if(curMenu=="start")
        {
            fadingToLeave=true;
        }
        else
        {
            curMenu="start";
            menuStart(&m_buttons);
        }
    }



    if(leftClic && name=="quit")
    {
        fadingToLeave=true;
    }
    if(leftClic && name=="linkocraftcom")
    {
        char url[255]="www.linkocraft.com";
        ShellExecute(NULL, "open", url,NULL, NULL, SW_SHOWNORMAL);
    }



    for(unsigned int i=0;i<m_buttons.size();i++)
        m_buttons[i].updateCursor(Vector3D(lastCursorX,lastCursorY,0));

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




string Menu::inputString(string txt,string msg,bool onlyInt)
{
    string savetxt=txt;
    vector<Button> b;
    b.clear();
    unsigned int ind=b.size();
    b.push_back(Button());
    b[ind].setPos(Vector3D(0.25,0.15,0));
    b[ind].setSize(Vector3D(0.5,0.6,0));
    b[ind].setName("inputtext");
    b[ind].ini();
    b[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/box_large.png"));
    b[ind].setClicable(false);

    ind=b.size();
    b.push_back(Button());
    b[ind].setPos(Vector3D(0.31,0.425,0));
    b[ind].setSize(Vector3D(0.375,0.075,0));
    b[ind].setName("input");
    b[ind].ini();
    b[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/input_large.png"));;
    b[ind].setClicable(false);


    ind=b.size();
    b.push_back(Button());
    b[ind].setPos(Vector3D(0.4,0.51,0));
    b[ind].setSize(Vector3D(0.175,0.2,0));
    b[ind].addText(msg);
    b[ind].setName("msg");
    b[ind].ini();
    b[ind].setClicable(false);
    b[ind].setTexture(NULL);
    b[ind].centerText(false);

    ind=b.size();
    b.push_back(Button());
    b[ind].setPos(Vector3D(0.28,0.3,0));
    b[ind].setSize(Vector3D(0.175,0.075,0));
    b[ind].setName("paste");
    b[ind].addText("Paste");
    b[ind].ini();
    b[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_small.png"));

    ind=b.size();
    b.push_back(Button());
    b[ind].setPos(Vector3D(0.54,0.3,0));
    b[ind].setSize(Vector3D(0.175,0.075,0));
    b[ind].setName("ok");
    b[ind].addText("Ok");
    b[ind].ini();
    b[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_small.png"));

    ind=b.size();
    b.push_back(Button());
    b[ind].setPos(Vector3D(0.32,0.4,0));
    b[ind].setSize(Vector3D(0.175,0.2,0));
    b[ind].addText(txt);
    b[ind].setName("txt");
    b[ind].ini();
    b[ind].centerText(false);
    b[ind].setClicable(false);
    b[ind].setTexture(NULL);

    SDL_EnableKeyRepeat(200, 45);

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
                playLoop=false;
                command="quit";
                fadingToLeave=true;
                txt=savetxt;
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

                    //cerr<<"add char "<< txt<<endl;
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




bool Menu::messageSure()
{
    bool result=false;

    vector<Button> b;
    b.clear();
    unsigned int ind=b.size();
    b.push_back(Button());
    b[ind].setPos(Vector3D(0.25,0.15,0));
    b[ind].setSize(Vector3D(0.5,0.6,0));
    b[ind].setName("sure");
    b[ind].ini();
    b[ind].setClicable(false);
    b[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/box_large.png"));

    ind=b.size();
    b.push_back(Button());
    b[ind].setPos(Vector3D(0.4,0.5,0));
    b[ind].setSize(Vector3D(0.175,0.075,0));
    b[ind].setName("suretxt");
    b[ind].addText("Are you sure?");
    b[ind].ini();
    b[ind].setTexture(NULL);
    b[ind].setClicable(false);

    ind=b.size();
    b.push_back(Button());
    b[ind].setPos(Vector3D(0.28,0.3,0));
    b[ind].setSize(Vector3D(0.175,0.075,0));
    b[ind].setName("yes");
    b[ind].addText("Yes");
    b[ind].ini();
    b[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_small.png"));

    ind=b.size();
    b.push_back(Button());
    b[ind].setPos(Vector3D(0.54,0.3,0));
    b[ind].setSize(Vector3D(0.175,0.075,0));
    b[ind].setName("no");
    b[ind].addText("No");
    b[ind].ini();
    b[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_small.png"));

    bool loop=true;
    while (loop)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                loop = false;
                fadingToLeave=true;
                playLoop=false;
                command="quit";
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
                            if(b[i].getName()=="yes")
                            {
                                Gsounds::getInstance()->play("../data/sounds/hover.mp3");
                                loop=false;
                                result=true;
                                break;
                            }
                            else if(b[i].getName()=="no")
                            {
                                Gsounds::getInstance()->play("../data/sounds/hover.mp3");
                                loop=false;
                                result=false;
                                break;
                            }
                        }
                    }
                }
                break;


                case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        loop=false;
                        result=false;
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


    return result;
}



void Menu::messageError(string msg)
{
    vector<Button> b;
    b.clear();
    unsigned int ind=b.size();
    b.push_back(Button());
    b[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/box_large.png"));
    b[ind].setPos(Vector3D(0.25,0.15,0));
    b[ind].setSize(Vector3D(0.5,0.6,0));
    b[ind].setName("error");
    b[ind].setClicable(false);

    ind=b.size();
    b.push_back(Button());
    b[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/blackbox.png"));
    b[ind].setPos(Vector3D(0.29,0.32,0));
    b[ind].setSize(Vector3D(0.42,0.22,0));
    b[ind].setName("blackbox");
    b[ind].setClicable(false);

    ind=b.size();
    b.push_back(Button());
    b[ind].setPos(Vector3D(0.45,0.55,0));
    b[ind].addText("Error:");
    b[ind].setName("errortxt");
    b[ind].ini();
    b[ind].centerText(false);
    b[ind].setClicable(false);
    b[ind].setTexture(NULL);

    ind=b.size();
    b.push_back(Button());
    b[ind].setPos(Vector3D(0.3,0.43,0));
    b[ind].addText(msg);
    b[ind].setName("errortxt");
    b[ind].ini();
    b[ind].centerText(false);
    b[ind].setClicable(false);
    b[ind].setTexture(NULL);

    ind=b.size();
    b.push_back(Button());
    b[ind].setPos(Vector3D(0.415,0.17,0));
    b[ind].setSize(Vector3D(0.175,0.075,0));
    b[ind].setName("ok");
    b[ind].addText("Ok");
    b[ind].ini();
    b[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_small.png"));

    bool loop=true;
    while (loop)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                loop = false;
                fadingToLeave=true;
                playLoop=false;
                command="quit";
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
                            if(b[i].getName()=="ok")
                            {
                                Gsounds::getInstance()->play("../data/sounds/hover.mp3");
                                loop=false;
                                break;
                            }
                        }
                    }
                }
                break;


                case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        loop=false;
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
}
