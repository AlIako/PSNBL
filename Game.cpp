#include "Game.h"

Game::Game()
{
    m_incontrol=true;
}

void Game::ini()
{
    grabCursor=true;

    m_video.ini();

    unsigned int ind=playerList.size();
    playerList.push_back(new Player());
    playerList[ind]->gtext=gtext;
    playerList[ind]->ini();

    //online
    m_online.ini();

    if(m_online.m_server)
        playerList[0]->setIdOnline(0);

    if(!m_online.m_server)
    {
        m_incontrol=false;

        GTime start_try_connect;
        start_try_connect.reset();
        while(!m_online.m_connectionEstablished && !start_try_connect.ecouler(2500))
        {
            start_try_connect.couler();
            m_online.update();
            SDL_Delay(50);
        }
        updateMultiplayer();
    }
    //end ini online

    m_map.m_incontrol=m_incontrol;
    m_map.gtext=gtext;
    m_map.online=&m_online;
    m_map.ini();
    m_map.playerList=&playerList;

    m_camera.setCible(playerList[0]);


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
                    Vector3D dir=Vector3D(0,0,sin((-m_camera.getBeta()+8*0)*M_PI/180))+playerList[0]->getDir();
                    dir=(m_camera.getTarget()-(playerList[0]->getPos()+Vector3D(0,0,1))).normalize();
                    playerList[0]->linkRope(m_map.createRope(playerList[0]->getPos(),dir));

                    infosSocket s;
                    s.type=2;

                    s.variable[1]=playerList[0]->getPos().X;
                    s.variable[2]=playerList[0]->getPos().Y;
                    s.variable[3]=playerList[0]->getPos().Z;
                    s.variable[4]=dir.X;
                    s.variable[5]=dir.Y;
                    s.variable[6]=dir.Z;

                    m_online.sendSocket(s);//add socket to queue
                }
                if(event.button.button==SDL_BUTTON_RIGHT)
                {
                    playerList[0]->unlinkRope();

                    infosSocket s;
                    s.type=3;
                    m_online.sendSocket(s);//add socket to queue
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
                    s.type=3;
                    m_online.sendSocket(s);//add socket to queue
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
                    if(m_incontrol)
                    {
                        infosSocket s;
                        s.type=6;
                        m_online.sendSocket(s);//add socket to queue


                        m_map.restart();
                    }
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
        m_online.update();

        m_map.update(ft);


        //draw
        m_video.beforeDraw();

        m_camera.look();



        for(unsigned int i=1, count=playerList.size();i<count;i++)
            playerList[i]->draw();

        m_map.draw();


        m_video.afterDraw();

        SDL_Delay(10);
    }


    close();
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
    infosSocket s;

    //send

    //send player position and angle
    s.type=1;

    s.variable[1]=playerList[0]->getPos().X;
    s.variable[2]=playerList[0]->getPos().Y;
    s.variable[3]=playerList[0]->getPos().Z;
    s.variable[4]=playerList[0]->getRot().Z;

    m_online.sendSocketReplace(s);//add socket to queue


    //cerr<<"received "<<m_online.socketsReceived.size()<<" sockets..."<<endl;
    //receive
    for(int i = 0;i<RECEIVE_SOCKET_HANDLE_PER_FRAME;i++)
    {
        s=m_online.getNextSocketRemove();//get next socket on the queue
        if(s.type!=-1)//if something on the list
        {
            //cerr<<"received socket type "<<(int)s.type<<", "<<s.variable[0]<<", "<<s.variable[1]<<", "<<s.variable[2]<<", "<<s.variable[3]<<endl;

            //seek player to update for this id
            int idPlayer=floor(s.variable[0]);
            Player *player=playerForId(idPlayer);
            //if player not found, create it and assign id
            if(player==NULL && s.type!=5)
            {
                unsigned int ind=playerList.size();
                playerList.push_back(new Player());
                playerList[ind]->gtext=gtext;
                playerList[ind]->ini();
                playerList[ind]->setIdOnline(idPlayer);
                player=playerList[ind];
                cerr<<"creating new player, id online: "<<idPlayer<<endl;
            }


            //player position and angle
            if(s.type==1)
            {
                player->setPos(Vector3D(s.variable[1],s.variable[2],s.variable[3]));
                player->setRot(Vector3D(0,0,s.variable[4]));
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
                playerList[ind]->gtext=gtext;
                playerList[ind]->ini();
                playerList[ind]->setIdOnline(idPlayer);
            }
            //you just connected and got response from server and your id
            if(s.type==5)
            {
                playerList[0]->setIdOnline(idPlayer);

                //send request for patterns
                infosSocket s;
                s.type=8;
                s.variable[0]=idPlayer;
                m_online.sendSocket(s);


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
            //pattern/lava lvl or request for patterns/lava lvl
            if(s.type==8)
            {
                if(m_online.m_server)
                {
                    cerr<<"sending pattern/lava lvl "<< floor(s.variable[1]) <<" to client"<<endl;
                    //send lava level and pattern queue to client
                    infosSocket s;
                    s.type=8;
                    s.variable[0]=0;
                    s.variable[1]=m_map.getLavaLevel();

                    std::vector<Pattern*>* pq=m_map.getPhase()->getPatternQueue();
                    //cerr<<"sending pattern/lava lvl "<< pq->size() <<" to client"<<endl;
                    unsigned int j=0;
                    for(unsigned int count=pq->size();j<count;j++)
                    {
                        cerr<<"send pat  "<< j <<" to client"<<endl;
                        s.variable[j+2]=(*pq)[j]->getPID();
                    }
                    s.variable[j+2]=-1;
                        cerr<<"sending pattern/lava lvl "<< j <<" to client"<<endl;

                    m_online.sendSocket(s);
                }
                else
                {
                    cerr<<"received pattern/lava lvl "<< floor(s.variable[1]) <<" from server!"<<endl;

                    if(floor(s.variable[1])!=-1)
                        m_map.setLavaLevel(floor(s.variable[1]));

                    for(int j =2;j<24;j++)
                    {
                        cerr<<"rec pat  "<< floor(s.variable[j]) <<" from server!"<<endl;
                        if(s.variable[j]==-1)
                            break;
                        //add pattern to queue
                        m_map.addPatternToQueue(floor(s.variable[j]));
                    }
                }
            }
            //lava level
            if(s.type==9)
            {

            }
            //rez all
            if(s.type==10)
            {

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
    m_online.close();
    m_video.close();

    cerr<<"Exited cleanly.";
}


Game::~Game()
{

}




