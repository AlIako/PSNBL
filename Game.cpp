#include "Game.h"

Game::Game()
{
}

void Game::ini()
{
    grabCursor=true;

    m_video=Video::getInstance();
    m_video->ini();

    unsigned int ind=playerList.size();
    playerList.push_back(new Player());
    playerList[ind]->ini();

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
    //end ini online

    m_map.ini();
    m_map.playerList=&playerList;

    m_camera.setCible(playerList[0]);
    m_mode="play";
    m_camera.setMode(m_mode);


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

                case SDL_MOUSEBUTTONUP:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    if(m_mode=="play")
                    {
                        Vector3D dir=Vector3D(0,0,sin((-m_camera.getBeta()+8*0)*M_PI/180))+playerList[0]->getDir();
                        dir=(m_camera.getTarget()-(playerList[0]->getPos()+Vector3D(0,0,1))).normalize();
                        playerList[0]->linkRope(m_map.createRope(playerList[0]->getPos(),dir));

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
                    playerList[0]->jump();

                    infosSocket s;
                    s.confirmationID=-1;
                    s.type=3;
                    m_online->sendSocket(s);//add socket to queue
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
                    case SDLK_e:
                    playerList[0]->pressKey(KEY_E,false);
                    break;
                    case SDLK_r:
                    if(Online::getInstance()->inControl())
                    {
                        infosSocket s;
                        s.confirmationID=m_online->nextConfirmationID();
                        s.type=6;
                        m_online->sendSocket(s);//add socket to queue


                        m_map.restart();

                        m_camera.setCible(playerList[0]);
                        m_camera.setMode("play");
                        m_mode="play";
                    }
                    break;
                    case SDLK_k:
                    playerList[0]->setLife(0);
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
        m_online->update();

        m_video->update(ft);
        m_map.update(ft);

        updateCamMode();


        //draw
        m_video->beforeDraw();

        m_camera.look();


        if(m_mode!="play")
            playerList[0]->draw();
        for(unsigned int i=1, count=playerList.size();i<count;i++)
            playerList[i]->draw();

        m_map.draw();


        m_video->afterDraw();

        SDL_Delay(10);
    }


    close();
}

void Game::updateCamMode()
{
    if(m_camera.getCible()->getLife()<=0)
    {
        Object* p=m_camera.getCible();
        for(unsigned int i=1, count=playerList.size();i<count;i++)
        {
            if(playerList[i]->getLife()>0)
                p=playerList[i];
        }
        m_mode="spectate";
        m_camera.setMode("spectate");
        m_camera.setCible(p);
    }
}

void Game::switchSpectate(int d)
{
    int id=0;
    Object* p=m_camera.getCible();

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
        }
    }
    for(int i=0;i<id;i++)
    {
        if(!foundPl && playerList[i]->getLife()>0)
        {
            foundPl=true;
            p=playerList[i];
        }
    }
    m_camera.setCible(p);
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
                if(player==NULL && s.type!=5 && idPlayer>=0 && idPlayer<30)//idPlayer<10 = sux fix temporaire
                {
                    unsigned int ind=playerList.size();
                    playerList.push_back(new Player());
                    playerList[ind]->ini();
                    playerList[ind]->setIdOnline(idPlayer);
                    player=playerList[ind];
                    cerr<<"creating new player, id online: "<<idPlayer<<endl;
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
                        Vector3D pos=Vector3D(s.variable[1],s.variable[2],s.variable[3]);
                        Vector3D dir=Vector3D(s.variable[4],s.variable[5],s.variable[6]);
                        player->linkRope(m_map.createRope(pos,dir));
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
                    //you just connected and got response from server and your id
                    if(s.type==5)
                    {
                        playerList[0]->setIdOnline(idPlayer);
    /*
                        //send request for patterns
                        infosSocket s;
                        s.type=8;
                        s.variable[0]=idPlayer;
                        m_online.sendSocket(s);*/


                        //first create all the players (i'd need to receive playerN from server)
                        /*for(int i=0;i<playerN;i++)
                        {
                            unsigned int ind=playerList.size();
                            playerList.push_back(new Player());
                            playerList[ind]->gtext=gtext;
                            playerList[ind]->ini();
                        }*/
                    }
                    //restart map
                    if(s.type==6)
                    {
                        m_map.restart();
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
                                    m_camera.setCible(playerList[0]);
                                    m_camera.setMode("play");
                                    m_mode="play";
                                }
                            }
                            o->setLife(0);
                        }
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
    m_online->close();
    m_video->close();

    cerr<<"Exited cleanly.";
}


Game::~Game()
{

}




