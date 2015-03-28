#include "Game.h"
Game::Game()
{
    pathTest="";
    command="menu";
}


void Game::ini()
{
    m_fps=0;
    m_fpsTime.reset();

    shiftPushed=false;

    grabCursor=true;
    levelEnded=false;

    //video
    m_video=Video::getInstance();

    Gsounds::getInstance()->loads();


    //player ini
    unsigned int ind=playerList.size();
    playerList.push_back(new Player());
    playerList[ind]->ini();


    //interface
    Interface::getInstance()->setTarget(playerList[0]);
    Interface::getInstance()->ini();
    //chat
    m_chat.activate(m_video->getWidth(), m_video->getHeight(), "../data/fonts/arial.TTF");
    m_chat.setSide(0);
    //tracer
    Tracer::getInstance()->enable();

    //online
    m_online=Online::getInstance();
    if(m_online->active())
    {
        if(m_online->m_server)
        {
            playerList[0]->setIdOnline(0);
            m_online->startThreads();
        }
        else
        {
            updateMultiplayer();
            //threads already started (menu)
        }

        playerList[0]->setOnlineName(m_online->getOnlineName());
    }
    else
    {
        m_online->setIncontrol(true);
        playerList[0]->setOnlineName("");
    }
    //end ini online

    Map::getInstance()->playerList=&playerList;
    Map::getInstance()->ini(pathTest);
    playerList[0]->setPos(Map::getInstance()->getStartPos());

    m_camera.setCible(playerList[0]);
    m_mode="play";
    m_camera.setMode(m_mode);

    SDL_ShowCursor(SDL_DISABLE);//pas de curseur
    SDL_WM_GrabInput(SDL_GRAB_ON);
    grabCursor=true;


    Lighting* l=Lighting::getInstance();
    l->setActive(true);
    l->shineAmbiant();

    if(l->getSize()==0)
        for(int i=0;i<4-3;i++)
        {
            l->addLight();
            l->setX("last",30*(pow(-1,i)));
            l->setY("last",30*(pow(-1,i+1)));
            l->setZ("last",10);

            l->setR("last",255);
            l->setG("last",153);
            l->setB("last",0);
            l->setAT("last",0.0001);
        }



    m_video->getFade()->startFadeOut();
    Video::getInstance()->getFade()->setR(0);
    Video::getInstance()->getFade()->setG(0);
    Video::getInstance()->getFade()->setB(0);
}


void Game::play(string path)
{
    pathTest=path;
    ini();

    //SDL_EnableKeyRepeat(10, 0);


    playLoop=true;
    fadingToLeave=false;

    while (playLoop)
    {

        if(m_chat.boxOpened())
            m_chat.checkKeyboard();
        else
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                fadingToLeave=true;
                command="menu";
                break;

                case SDL_MOUSEMOTION:
                m_camera.onMouseMotion(event.motion);
                break;

                case SDL_MOUSEBUTTONUP:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    if(m_mode=="play")
                    {
                        if(playerList[0]->getLife()>0)
                        {
                            Vector3D dir=(m_camera.getTarget()-(playerList[0]->getPos()+Vector3D(0,0,1))).normalize();

                            if(castSpell(playerList[0],"rope",dir))
                            {
                                infosSocket s;
                                s.confirmationID=-1;
                                s.type=2;

                                s.variable[1]=playerList[0]->getPos().X;
                                s.variable[2]=playerList[0]->getPos().Y;
                                s.variable[3]=playerList[0]->getPos().Z;
                                s.variable[4]=dir.X;
                                s.variable[5]=dir.Y;
                                s.variable[6]=dir.Z;

                                m_online->sendSocket(s);//add socket to queue
                            }
                        }

                    }
                    else if(m_mode=="spectate")
                    {
                        switchSpectate(1);
                    }
                }
                if(event.button.button==SDL_BUTTON_RIGHT)
                {
                    if(m_mode=="play")
                    {
                        if(playerList[0]->getLife()>0)
                        {
                            playerList[0]->unlinkRope();

                            infosSocket s;
                            s.confirmationID=-1;
                            s.type=3;
                            m_online->sendSocket(s);//add socket to queue
                        }
                    }
                    else if(m_mode=="spectate")
                    {
                        switchSpectate(-1);
                    }
                }
                if(event.button.button==SDL_BUTTON_WHEELUP)
                {
                    Video::getInstance()->incrFOV(1);
                }
                if(event.button.button==SDL_BUTTON_WHEELDOWN)
                {
                    Video::getInstance()->incrFOV(-1);
                }
                break;

                case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_KP_ENTER:
                    if(m_chat.active())
                        m_chat.openTextBox(playerList[0]->getIdOnline(),0.1);
                    break;
                    case SDLK_RETURN:
                    if(m_chat.active())
                        m_chat.openTextBox(playerList[0]->getIdOnline(),0.1);
                    break;
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
                    case SDLK_e:
                    playerList[0]->pressKey(KEY_E,true);
                    break;
                    case SDLK_SPACE:
                    if(playerList[0]->getLife()>0)
                    {
                        if(shiftPushed)
                        {
                            if(castSpell(playerList[0],"longjump"))
                            {
                                infosSocket s;
                                s.confirmationID=-1;
                                s.type=15;

                                s.variable[1]=playerList[0]->getPos().X;
                                s.variable[2]=playerList[0]->getPos().Y;
                                s.variable[3]=playerList[0]->getPos().Z;

                                m_online->sendSocket(s);//add socket to queue
                            }

                        }
                        else
                            castSpell(playerList[0],"jump");
                    }
                    break;

                    case SDLK_LSHIFT:
                        playerList[0]->setGasing(true);
                        shiftPushed=true;
                    break;
                    default:
                    break;
                }
                break;

                case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_KP_ENTER:
                    if(m_chat.active())
                        m_chat.enterUp();
                    break;
                    case SDLK_RETURN:
                    if(m_chat.active())
                        m_chat.enterUp();
                    break;
                    case SDLK_ESCAPE:
                    fadingToLeave=true;
                    command="menu";
                    break;
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
                    case SDLK_e:
                    playerList[0]->pressKey(KEY_E,false);
                    break;
                    case SDLK_r:
                    if(playerList.size()==1 &&
                       (!Online::getInstance()->active() || Online::getInstance()->inControl()))//if youre alone its ok
                    {
                        infosSocket s;
                        s.confirmationID=m_online->nextConfirmationID();
                        s.type=6;
                        m_online->sendSocket(s);//add socket to queue


                        Map::getInstance()->restart();

                        Interface::getInstance()->setTarget(playerList[0]);
                        m_camera.setCible(playerList[0]);
                        m_camera.setMode("play");
                        m_mode="play";

                        m_chat.newMessage("Map reset.",-2);
                    }
                    break;
                    case SDLK_k:
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
                    case SDLK_LSHIFT:
                        playerList[0]->setGasing(false);
                        shiftPushed=false;
                    break;
                    case SDLK_SPACE:
                    if(playerList[0]->getLife()>0)
                    {
                        if(shiftPushed)
                        {
                            if(castSpell(playerList[0],"longjump"))
                            {
                                infosSocket s;
                                s.confirmationID=-1;
                                s.type=15;

                                s.variable[1]=playerList[0]->getPos().X;
                                s.variable[2]=playerList[0]->getPos().Y;
                                s.variable[3]=playerList[0]->getPos().Z;

                                m_online->sendSocket(s);//add socket to queue
                            }

                        }
                        else
                            castSpell(playerList[0],"jump");
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
        m_online->update();

        Gsounds::getInstance()->update(m_camera.getPos().toLeft(),Vector3D(0,0,0),m_camera.getDir().toLeft(),Vector3D(0,0,1));

        m_video->update(ft);
        Map::getInstance()->update(ft);

        Effects::getInstance()->update(ft);

        Tracer::getInstance()->traceCerr("debug","1");

        Interface::getInstance()->setMode(m_mode);
        Interface::getInstance()->update(ft);
        handleCommands();
        handleTracer();

        Tracer::getInstance()->traceCerr("debug","2");

        updateCamMode();

        //you just died
        if(playerList[0]->getLife()<=0 && !alreadyDead)
        {
            alreadyDead=true;
            Interface::getInstance()->warning("../data/textures/interface/warning/died.png",0.03);


            //send chat msg
            stringstream ss;
            int dc=playerList[0]->getDeathCause();

            if(dc==0)
                ss << playerList[0]->getOnlineName() << " mysteriously died.";
            else if(dc==1)
                ss << playerList[0]->getOnlineName() << " burned to death.";
            else if(dc==2)
                ss << playerList[0]->getOnlineName() << " committed suicide.";
            else if(dc==3)
                ss << playerList[0]->getOnlineName() << " exploded in pieces.";

            char* tempChar=stringtochar(ss.str());
            m_chat.newMessage(tempChar,-2);
            delete tempChar;
        }
        else if(playerList[0]->getLife()>0)
            alreadyDead=false;

        Tracer::getInstance()->traceCerr("debug","3");

        //endlevel
        if(checkEndLevel())
            endLevel();

        //crosshair
        Map::getInstance()->simulateRopeForCrosshair(playerList[0],
                                       (m_camera.getTarget()-(playerList[0]->getPos()+Vector3D(0,0,1))).normalize(),
                                       Interface::getInstance()->getCrosshair());

        draw();

        m_video->afterDraw();

        //fps calcul
        m_fps++;
        m_fpsTime.couler();
        if(m_fpsTime.ecouler(1000))
        {
            Interface::getInstance()->setFPS(m_fps);
            m_fps=0;
            m_fpsTime.reset();
        }

        Tracer::getInstance()->traceCerr("debug","8");

        SDL_Delay(10);



        if(fadingToLeave)
        {
            if(Video::getInstance()->getFade()->getFading()==false)
            {
                Video::getInstance()->getFade()->setR(0);
                Video::getInstance()->getFade()->setG(0);
                Video::getInstance()->getFade()->setB(0);
                Video::getInstance()->getFade()->startFadeIn();
            }
            if(Video::getInstance()->getFade()->getAlpha()>=1)
            {
                playLoop=false;
                fadingToLeave=false;
            }
        }
    }


    close();
}

void Game::draw()
{
    //draw
    m_video->beforeDraw();

    m_camera.look();

    Lighting::getInstance()->shineAmbiant();
    Lighting::getInstance()->shineAll();


    Tracer::getInstance()->traceCerr("debug","4");

    //glUseProgram(m_video->programIDRed);

    if(m_mode!="play")
        playerList[0]->draw();
    for(unsigned int i=1, count=playerList.size();i<count;i++)
        playerList[i]->draw();

    Tracer::getInstance()->traceCerr("debug","5");


    //glUseProgram(m_video->programIDWave);

    Map::getInstance()->draw();
    Effects::getInstance()->draw();

    //glUseProgram(m_video->programID);
    if(Map::getInstance()->getLava())
        if(m_camera.getPos().Z<=Map::getInstance()->getLava()->getPos().Z+Map::getInstance()->getLava()->getSize().Z*2)
            Interface::getInstance()->drawScreenEffect("../data/textures/lava.png");

    Tracer::getInstance()->traceCerr("debug","6");


    //interface
    Interface::getInstance()->draw();
    m_chat.draw();


    Tracer::getInstance()->traceCerr("debug","7");


    //fading
    m_video->matrixOrtho2D();
    m_video->getFade()->draw();
    m_video->matrixProjection();

    //interface warning
    Interface::getInstance()->drawWarning();

}
