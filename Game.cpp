#include "Game.h"
Game::Game()
{
}


void Game::ini()
{
    m_fps=0;
    m_fpsTime.reset();

    shiftPushed=false;

    grabCursor=true;

    //video
    m_video=Video::getInstance();

    //sound
    Gsounds::getInstance()->ini();
    Gsounds::getInstance()->loads();



    //player ini
    unsigned int ind=playerList.size();
    playerList.push_back(new Player());
    playerList[ind]->ini();


    //interface
    m_interface.setTarget(playerList[0]);
    m_interface.ini();
    //chat
    m_chat.activate(m_video->getWidth(), m_video->getHeight(), "../data/fonts/arial.TTF");
    m_chat.setSide(0);
    //tracer
    Tracer::getInstance()->enable();

    //online
    m_online=Online::getInstance();
    m_online->ini();
    if(m_online->active())
    {
        if(m_online->m_server)
            playerList[0]->setIdOnline(0);

        if(!m_online->m_server)
        {
            m_online->setIncontrol(false);

            GTime start_try_connect;
            start_try_connect.reset();
            while(!m_online->m_connectionEstablished && !start_try_connect.ecouler(2500))
            {
                start_try_connect.couler();
                m_online->update();
                SDL_Delay(50);
            }
            updateMultiplayer();
        }
    }
    playerList[0]->setOnlineName(m_online->getOnlineName());
    //end ini online

    m_map.ini();
    m_map.playerList=&playerList;

    m_camera.setCible(playerList[0]);
    m_mode="play";
    m_camera.setMode(m_mode);

    SDL_ShowCursor(SDL_DISABLE);//pas de curseur
    SDL_WM_GrabInput(SDL_GRAB_ON);
    grabCursor=true;
}

void Game::playPlayerSound(Player* p,string sound)
{
    if(Gsounds::getInstance()->getSound(sound)!=NULL)
    {

        if(p==playerList[0])//if current player, normal sound
            Gsounds::getInstance()->play(sound);
        else//if other player, sound 3D
        {
            Gsounds::getInstance()->getSound(sound)->setPos(p->getPos().toLeft());
            Gsounds::getInstance()->play(sound,1,20,80);
        }
    }
}

void Game::handleTracer()
{
    //traces
    vector<Trace*>* traces=Tracer::getInstance()->getTraces();
    if(traces->size()>0)
    {
        for(unsigned int i=0;i<traces->size();i++)
        {
            if(!(*traces)[i]->sent)
            {
                (*traces)[i]->sent=true;
                m_chat.newMessage((*traces)[i]->msg,-1);
            }
        }
        Tracer::getInstance()->afterFetch();
    }
}

void Game::handleCommands()
{
    for(unsigned int i=0;i<m_chat.commands.size();i++)
    {
        string c=m_chat.commands[i];
        if(c=="/restart" || c=="/reset" || c=="/Reset" || c=="/Restart" || c=="/R" || c=="/r")
        {
            if(Online::getInstance()->inControl())
            {
                infosSocket s;
                s.confirmationID=m_online->nextConfirmationID();
                s.type=6;
                m_online->sendSocket(s);//add socket to queue


                m_map.restart();

                m_interface.setTarget(playerList[0]);
                m_camera.setCible(playerList[0]);
                m_camera.setMode("play");
                m_mode="play";

                m_chat.newMessage("Map reset.",-2);
            }
        }
        else if(c=="/kill" || c=="/suicide")
        {
            playerList[0]->setLife(0);
            playerList[0]->setDeathCause(2);
        }
        else if(c=="/pos" || c=="/position")
        {
            //command not found
            stringstream ss;
            ss << "Current position is "<<playerList[0]->getPos().toString();
            char* tempChar=stringtochar(ss.str());
            m_chat.recieveMessage(tempChar,0,-2);
            delete tempChar;
        }
        else if(c.find("/tracer")!=string::npos)
        {
            if(c.find("enable")!=string::npos)
            {
                Tracer::getInstance()->enable();
                m_chat.recieveMessage("Tracer enabled.",0,-2);
            }
            else if(c.find("disable")!=string::npos)
            {
                Tracer::getInstance()->disable();
                m_chat.recieveMessage("Tracer disabled.",0,-2);
            }
            else if(c.find("clear channels")!=string::npos)
            {
                Tracer::getInstance()->clearChannels();
                m_chat.recieveMessage("Tracer channels cleared.",0,-2);
            }
            else if(c.find("reset")!=string::npos)
            {
                Tracer::getInstance()->reset();
                m_chat.recieveMessage("Tracer channels cleared.",0,-2);
            }
            else if(c.find("add")!=string::npos)
            {
                string ch=c.substr(c.find("add")+4,c.size());
                Tracer::getInstance()->addChannel(ch);

                char* tempChar=stringtochar("Tracer Channel "+ch+" added.");
                m_chat.recieveMessage(tempChar,0,-2);
                delete tempChar;
            }
        }
        else if(c.find("/p")!=string::npos)
        {
            if(c.find("gh")!=string::npos)
            {
                playerList[0]->setPos(Vector3D(0,0,300)+playerList[0]->getPos());
            }
        }
        else
        {
            //command not found
            stringstream ss;
            ss << "\""<< c << "\" command not found.";
            char* tempChar=stringtochar(ss.str());
            m_chat.recieveMessage(tempChar,0,-2);
            delete tempChar;
        }
    }
    m_chat.commands.clear();
}


bool Game::castSpell(Player* p, string spell, Vector3D param1)
{
    if(p!=NULL)
    {
        Spell* s=p->getSpell(spell);
        if(s!=NULL)
        {
            if(s->cast())
            {
                if(s->getName()=="rope")
                {
                    p->linkRope(m_map.createRope(p->getPos(),param1));

                    playPlayerSound(p,"../data/sounds/bounce.wav");
                }
                else if(s->getName()=="jump")
                {
                    p->jump();
                    //Gsounds::getInstance()->play("../data/sounds/bounce.wav");
                }
                else if(s->getName()=="longjump")
                {
                    p->setVel(p->getVel()+p->getDir()/3.0);
                    p->jump();
                    playPlayerSound(p,"../data/sounds/boost.wav");
                    //Gsounds::getInstance()->play("../data/sounds/bounce.wav");
                }
                return true;//spell cast successfull
            }
        }
    }
    return false;
}

void Game::play()
{
    ini();

    //SDL_EnableKeyRepeat(10, 0);

    SDL_Event event;

    playLoop=true;

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
                playLoop = false;
                break;

                case SDL_MOUSEMOTION:
                m_camera.onMouseMotion(event.motion);
                break;

                case SDL_MOUSEBUTTONUP:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    if(m_mode=="play")
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
                    else if(m_mode=="spectate")
                    {
                        switchSpectate(1);
                    }
                }
                if(event.button.button==SDL_BUTTON_RIGHT)
                {
                    if(m_mode=="play")
                    {
                        playerList[0]->unlinkRope();

                        infosSocket s;
                        s.confirmationID=-1;
                        s.type=3;
                        m_online->sendSocket(s);//add socket to queue
                    }
                    else if(m_mode=="spectate")
                    {
                        switchSpectate(-1);
                    }
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

                    //unlink rope
                    infosSocket s;
                    s.confirmationID=-1;
                    s.type=3;
                    m_online->sendSocket(s);//add socket to queue
                    break;
                    case SDLK_ESCAPE:
                    playLoop = false;
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
                    if(playerList.size()==1 && Online::getInstance()->inControl())//if youre alone its ok
                    {
                        infosSocket s;
                        s.confirmationID=m_online->nextConfirmationID();
                        s.type=6;
                        m_online->sendSocket(s);//add socket to queue


                        m_map.restart();

                        m_interface.setTarget(playerList[0]);
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
        m_map.update(ft);


        m_interface.setMode(m_mode);
        m_interface.update(ft);
        handleCommands();
        handleTracer();

        updateCamMode();

        //you just died
        if(playerList[0]->getLife()<=0 && !alreadyDead)
        {
            alreadyDead=true;


            //send chat msg
            stringstream ss;
            int dc=playerList[0]->getDeathCause();

            if(dc==0)
                ss << playerList[0]->getOnlineName() << " mysteriously died.";
            else if(dc==1)
                ss << playerList[0]->getOnlineName() << " burned to death.";
            else if(dc==2)
                ss << playerList[0]->getOnlineName() << " committed suicide.";

            char* tempChar=stringtochar(ss.str());
            m_chat.newMessage(tempChar,-2);
            delete tempChar;
        }
        else if(playerList[0]->getLife()>0)
            alreadyDead=false;

        //crosshair
        m_map.simulateRopeForCrosshair(playerList[0],
                                       (m_camera.getTarget()-(playerList[0]->getPos()+Vector3D(0,0,1))).normalize(),
                                       m_interface.getCrosshair());

        //draw
        m_video->beforeDraw();

        m_camera.look();


        //glUseProgram(m_video->programIDRed);

        if(m_mode!="play")
            playerList[0]->draw();
        for(unsigned int i=1, count=playerList.size();i<count;i++)
            playerList[i]->draw();


        //glUseProgram(m_video->programIDWave);

        m_map.draw();

        //glUseProgram(m_video->programID);

        if(m_camera.getPos().Z<=m_map.getLava()->getPos().Z+m_map.getLava()->getSize().Z*2)
            m_interface.drawScreenEffect("../data/textures/lava.png");

        m_interface.draw();
        m_chat.draw();



        m_video->afterDraw();

        //fps calcul
        m_fps++;
        m_fpsTime.couler();
        if(m_fpsTime.ecouler(1000))
        {
            m_interface.setFPS(m_fps);
            m_fps=0;
            m_fpsTime.reset();
        }

        SDL_Delay(10);
    }


    close();
}

void Game::updateCamMode()
{
    if(m_camera.getCible()->getLife()<=0)
    {
        //camera mode
        Player* pTarget=NULL;
        Object* p=m_camera.getCible();
        for(unsigned int i=1, count=playerList.size();i<count;i++)
        {
            if(playerList[i]->getLife()>0)
            {
                p=playerList[i];
                pTarget=playerList[i];
            }
        }
        m_mode="spectate";
        m_camera.setMode("spectate");
        m_camera.setCible(p);
        m_interface.setTarget(pTarget);
    }
}

void Game::switchSpectate(int d)
{
    int id=0;
    Object* p=m_camera.getCible();
    Player* pTarget=NULL;

    //find which id we have now
    for(unsigned int i=0, count=playerList.size();i<count;i++)
    {
        if(playerList[i]->getIdOnline()==p->getIdOnline())
            id=i;
    }

    //find next player in list that has no same id
    bool foundPl=false;
    for(unsigned int i=id+1, count=playerList.size();i<count;i++)
    {
        int tempI=i;
        if(!foundPl && playerList[tempI]->getLife()>0)
        {
            foundPl=true;
            p=playerList[tempI];
            pTarget=playerList[tempI];
        }
    }
    for(int i=0;i<id;i++)
    {
        if(!foundPl && playerList[i]->getLife()>0)
        {
            foundPl=true;
            p=playerList[i];
            pTarget=playerList[i];
        }
    }
    m_camera.setCible(p);
    m_interface.setTarget(pTarget);
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


void Game::updateMultiplayer()
{
    if(m_online->active())
    {
        infosSocket s;

        //send

        //send player position and angle
        s.type=1;
        s.confirmationID=-1;

        s.variable[1]=playerList[0]->getPos().X;
        s.variable[2]=playerList[0]->getPos().Y;
        s.variable[3]=playerList[0]->getPos().Z;
        s.variable[4]=playerList[0]->getRot().Z;
        s.variable[5]=playerList[0]->getLife();

        m_online->sendSocketReplace(s);//add socket to queue

        //chat messages
        for(unsigned int i=0;i<m_chat.msgToSend.size();i++)
        {
            s.type=13;
            s.confirmationID=m_online->nextConfirmationID();

            s.variable[1]=m_chat.msgToSend[i].user;
            if(m_chat.msgToSend[i].user>=0)
                s.variable[1]=playerList[0]->getIdOnline();

            int namewritten=0;
            std::string nametoWrite=playerList[0]->getOnlineName();
            for(int j=0;j<TEXT_SIZE;j++)
            {
                if(namewritten==-1)
                {
                    if(j<=(int)nametoWrite.size())
                    {
                        if(j==(int)nametoWrite.size())
                        {
                            s.text[j]=':';
                            s.text[j+1]=' ';
                        }
                        else s.text[j]=nametoWrite[j];
                    }
                    else namewritten=j+1;
                }
                else
                {
                    if(j-namewritten>=(int)m_chat.msgToSend[i].msg.size())
                        s.text[j]='\0';
                    else
                        s.text[j]=m_chat.msgToSend[i].msg[j-namewritten];
                }
            }
            cerr<<"Envoi du message "<<s.text<<endl;
            m_online->sendSocket(s);//add socket to queue

            //chat->newMessage(online->playerList[0]->name+" got eaten alive...",-2);
            /*if(m_chat.msgToSend[i].user==-1)
                m_chat.msgToSend[i].user=(*params->playerList)[0]->id;

            cerr << "msg to send : " << params->chat->msgToSend[i].user << endl;
            //send message avec le nom devant
            infosSocket infosSMSG;
            infosSMSG.type=4;//msg
            int namewritten=-1;

            string nametoWrite=(*params->playerList)[0]->name;
            if(params->chat->msgToSend[i].user==-2)
                namewritten=0;

            for(int j=0;j<TEXT_SIZE;j++)
            {
                if(namewritten==-1)
                {
                    if(j<=(int)nametoWrite.size())
                    {
                        if(j==(int)nametoWrite.size())
                        {
                            infosSMSG.texte[j]=':';
                            infosSMSG.texte[j+1]=' ';
                        }
                        else infosSMSG.texte[j]=nametoWrite[j];
                    }
                    else namewritten=j+1;
                }
                else
                {
                    if(j-namewritten>=(int)params->chat->msgToSend[i].msg.size())
                        infosSMSG.texte[j]='\0';
                    else
                        infosSMSG.texte[j]=params->chat->msgToSend[i].msg[j-namewritten];
                }
            }
            infosSMSG.variable[0]=params->chat->msgToSend[i].id;
            infosSMSG.variable[19]=params->chat->msgToSend[i].user;
            infosSMSG.variable[20]=(*params->playerList)[0]->id;*/

        }
        m_chat.msgToSend.clear();




        //cerr<<"received "<<m_online->socketsReceived.size()<<" sockets..."<<endl;
        //receive
        for(int i = 0;i<RECEIVE_SOCKET_HANDLE_PER_FRAME;i++)
        {
            s=m_online->getNextSocketRemove();//get next socket on the queue
            if(s.type!=-1)//if something on the list
            {
                //cerr<<"received socket type "<<(int)s.type<<", "<<s.variable[0]<<", "<<s.variable[1]<<", "<<s.variable[2]<<", "<<s.variable[3]<<endl;

                //seek player to update for this id
                int idPlayer=floor(s.variable[0]);
                Player *player=playerForId(idPlayer);
                //if player not found, create it and assign id
                if(player==NULL && s.type!=5 && s.type!=12 && idPlayer>=0 && idPlayer<30)//idPlayer<10 = sux fix temporaire
                {
                    unsigned int ind=playerList.size();
                    playerList.push_back(new Player());
                    playerList[ind]->ini();
                    playerList[ind]->setIdOnline(idPlayer);
                    player=playerList[ind];
                    cerr<<"creating new player, id online: "<<idPlayer<<endl;

                    /*//chat message
                    stringstream ss;
                    ss << "Player ";
                    ss << idPlayer << " joined.";
                    char* tempChar=stringtochar(ss.str());
                    m_chat.recieveMessage(tempChar,0,-2);
                    delete tempChar;*/
                }
                else if(s.type==5)//you just connected and got response from server and your id
                {
                    cerr<<"setting your online id to "<<idPlayer<<endl;
                    playerList[0]->setIdOnline(idPlayer);

                    //send your name, son.
                    infosSocket nameSocket;
                    nameSocket.confirmationID=m_online->nextConfirmationID();
                    nameSocket.type=14;//name
                    std::string nameToWrite=playerList[0]->getOnlineName();
                    for(int j=0;j<TEXT_SIZE;j++)
                    {
                        if(j<=(int)nameToWrite.size())
                            nameSocket.text[j]=nameToWrite[j];
                        else nameSocket.text[j]='\0';
                    }
                    m_online->sendSocket(nameSocket);
                }
                //if we found/created the player that sent us this message
                //we can finaly handle the received messages
                if(player)
                {

                    /*
                    socket types
                    1: player position, angle and life
                    2: hook
                    3: unhook
                    4: new player
                    5: you just connected and got response from server and your id
                    6:restart map
                    7:phase
                    8:next phase: pattern/lava lvl or request for patterns/lava lvl
                    9:lava level
                    10:loot bonus
                    11:socket confirmation
                    12:disconnect
                    13:chat msg
                    14: name
                    15: longjump
                    */
                    //player position and angle and life
                    if(s.type==1)
                    {
                        player->setPos(Vector3D(s.variable[1],s.variable[2],s.variable[3]));
                        player->setRot(Vector3D(0,0,s.variable[4]));
                        player->setLife(s.variable[5]);
                    }
                    //hook
                    if(s.type==2)
                    {
                        player->setPos(Vector3D(s.variable[1],s.variable[2],s.variable[3]));
                        Vector3D dir=Vector3D(s.variable[4],s.variable[5],s.variable[6]);

                        castSpell(player,"rope",dir);
                    }
                    //unhook
                    if(s.type==3)
                    {
                        player->unlinkRope();
                    }
                    //new player
                    if(s.type==4 && 0)
                    {
                        unsigned int ind=playerList.size();
                        playerList.push_back(new Player());
                        playerList[ind]->ini();
                        playerList[ind]->setIdOnline(idPlayer);
                    }
                    //player disconnected
                    if(s.type==12)
                    {
                        //chat msg
                        stringstream ss;
                        ss << "Player ";
                        ss << player->getOnlineName() << " left.";
                        char* tempChar=stringtochar(ss.str());

                        m_chat.recieveMessage(tempChar,0,-2);
                        delete tempChar;

                        //if server left
                        if(s.variable[0]==0)
                        {
                            stringstream ss2;
                            ss2 << "Server offline. You're alone.";
                            char* tempChar2=stringtochar(ss2.str());

                            m_chat.recieveMessage(tempChar2,0,-2);
                            delete tempChar2;
                        }


                        //delete player from player list
                        cerr<<"Player "<<s.variable[0]<< " disconnected. Deleting it from list."<<endl;
                        for(unsigned int j=0;j<playerList.size();j++)
                        {
                            if(playerList[j]->getIdOnline()==s.variable[0])
                            {
                                delete playerList[j];
                                playerList.erase(playerList.begin()+j);
                            }
                        }
                    }
                    //restart map
                    if(s.type==6)
                    {
                        m_map.restart();
                        m_interface.setTarget(playerList[0]);
                        m_camera.setCible(playerList[0]);
                        m_camera.setMode("play");
                        m_mode="play";

                        //send request for patterns
                       /* infosSocket s;
                        s.type=8;
                        s.variable[0]=playerList[0]->getIdOnline();
                        m_online.sendSocket(s);*/
                    }
                    //phase
                    if(s.type==7)
                    {
                        //set phase and ini
                    }
                    //next phase: pattern/lava lvl or request for patterns/lava lvl
                    if(s.type==8)
                    {
                        if(m_online->m_server)
                        {
                            //cerr<<"sending pattern/lava lvl "<< floor(s.variable[1]) <<" to client"<<endl;
                            //send lava level and pattern queue to client
                            infosSocket s;
                            s.confirmationID=m_online->nextConfirmationID();
                            s.type=8;
                            s.variable[0]=0;
                            s.variable[1]=m_map.getLavaLevel();

                            std::vector<Pattern*>* pq=m_map.getPhase()->getPatternQueue();
                            //start z from first pattern
                            if(pq->size()>0)
                                s.variable[2]=(*pq)[0]->getStartZ();
                            //cerr<<"sending pattern/lava lvl "<< pq->size() <<" to client"<<endl;
                            unsigned int j=0;
                            for(unsigned int count=pq->size();j<count;j++)
                            {
                                //cerr<<"send pat  "<< j <<" to client"<<endl;
                                s.variable[j+3]=(*pq)[j]->getPID();
                            }
                            s.variable[j+3]=-1;
                            //cerr<<"sending pattern/lava lvl "<< j <<" to client"<<endl;

                            m_online->sendSocket(s);
                        }
                        else
                        {
                            //cerr<<"received pattern/lava lvl "<< floor(s.variable[1]) <<" from server!"<<endl;

                            //go next phase
                            m_map.getPhase()->goToNextPhase();

                            //lava level
                            if(floor(s.variable[1])!=-1)
                                m_map.setLavaLevel(s.variable[1]);

                            std::vector<Pattern*>* pq=m_map.getPhase()->getPatternQueue();
                            for(int j =3;j<24;j++)
                            {
                                //cerr<<"rec pat  "<< floor(s.variable[j]) <<" from server!"<<endl;
                                if(s.variable[j]==-1)
                                    break;

                                //add pattern to queue
                                m_map.getPhase()->addPatternToQueue(floor(s.variable[j]));
                                //pattern start z from first pattern
                                if(j==3 && floor(s.variable[2])!=-1)
                                {
                                    (*pq)[pq->size()-1]->setStartZ(s.variable[2]);
                                }
                            }

                        }
                    }
                    //lava level
                    if(s.type==9)
                    {

                    }
                    //loot bonus
                    if(s.type==10)
                    {
                        Vector3D pos=Vector3D(s.variable[1],s.variable[2],s.variable[3]);
                        std::vector<Object*>* objects=m_map.getObjects();

                        //find nearest bonus (cant be farther than 5)
                        Object* o=NULL;
                        double distMax=5;

                        for(unsigned int i = 0, count = (*objects).size(); i<count;i++)
                        {
                            double tempDist=distance2V(pos,(*objects)[i]->getPos());
                            if((*objects)[i]->getType()=="bonus" && tempDist<distMax)
                            {
                                o=(*objects)[i];
                                distMax=tempDist;
                            }
                        }

                        //object found
                        if(o!=NULL)
                        {
                            if(o->getName()=="rez")
                            {
                                //rez bonus
                                cerr<<"resurecting!"<<endl;
                                if(playerList[0]->getLife()<=0)
                                {
                                    playerList[0]->resurrect();
                                    playerList[0]->setPos(pos);
                                    m_interface.setTarget(playerList[0]);
                                    m_camera.setCible(playerList[0]);
                                    m_camera.setMode("play");
                                    m_mode="play";
                                }
                            }
                            o->setLife(0);
                        }
                    }
                    //chat msg
                    if(s.type==13)
                    {
                        cerr<<"Message reçu: "<<s.text<<endl;

                        std::ostringstream oss;

                        if(s.variable[1]>=0)
                            oss << player->getOnlineName()<<": ";
                        oss << s.text;
                        char* tempChar=stringtochar(oss.str());
                        m_chat.recieveMessage(tempChar,0,s.variable[1]);
                        delete tempChar;
                    }
                    //get name
                    if(s.type==14)
                    {
                        std::string nameNoO=nameNoEnd(s.text,TEXT_SIZE);
                        cerr <<"Name "<<nameNoO<< " received."<<endl;
                        if(player->getOnlineName()=="unnamed")
                        {
                            if(nameNoO!="unnamed")
                            {
                                //chat message
                                stringstream ss;
                                ss << "Player "<< nameNoO << " joined.";
                                char* tempChar=stringtochar(ss.str());
                                m_chat.recieveMessage(tempChar,0,-2);
                                delete tempChar;
                            }

                            //if you didn't have this name, send yours back (be polite ffs è_é)
                            cerr<<"Sending my name back"<<endl;

                            infosSocket nameSocket;
                            nameSocket.confirmationID=m_online->nextConfirmationID();
                            nameSocket.type=14;//name
                            std::string nameToWrite=playerList[0]->getOnlineName();
                            for(int j=0;j<TEXT_SIZE;j++)
                            {
                                if(j<(int)nameToWrite.size())
                                    nameSocket.text[j]=nameToWrite[j];
                                else nameSocket.text[j]='\0';
                            }
                            m_online->sendSocket(nameSocket);
                        }

                        player->setOnlineName(nameNoO);
                    }
                    //long jump
                    if(s.type==15)
                    {
                        playPlayerSound(player,"../data/sounds/boost.wav");
                    }
                }
            }
        }
    }
}

Player* Game::playerForId(int id)
{
    for(unsigned int i=0,count=playerList.size();i<count;i++)
    {
        if(playerList[i]->getIdOnline()==id)
            return playerList[i];
    }
    return NULL;
}









void Game::close()
{
    if(m_online->active())
    {
        infosSocket s;
        s.type=12;
        s.confirmationID=-1;
        m_online->sendSocket(s);
        SDL_Delay(250);
    }
    m_online->close();


    cerr<<"Exited cleanly.";
}


Game::~Game()
{

}




