#include "Game.h"

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
        if(Online::getInstance()->m_server)
        {
            s.variable[6]=m_map.getLavaLevel();
            s.variable[7]=m_map.getLava()->getSpeed();
        }

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
                if(player==NULL && (s.type==4 ||s.type==14)
                    && s.type!=5 && s.type!=12 && idPlayer>=0 && idPlayer<30)//idPlayer<10 = sux fix temporaire
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



                    //send request for patterns
                    infosSocket s;
                    s.confirmationID=m_online->nextConfirmationID();
                    s.type=8;
                    m_online->sendSocket(s);
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
                    9:phase
                    10:loot bonus
                    11:socket confirmation
                    12:disconnect
                    13:chat msg
                    14: name
                    15: longjump
                    16: loot new spell
                    */
                    //player position and angle and life. Lava level too
                    if(s.type==1)
                    {
                        player->setPos(Vector3D(s.variable[1],s.variable[2],s.variable[3]));
                        player->setRot(Vector3D(0,0,s.variable[4]));
                        player->setLife(s.variable[5]);

                        if(!Online::getInstance()->m_server && s.variable[0]==0)
                        {
                            //lava level
                            m_map.setLavaLevel(s.variable[6]);
                            m_map.getLava()->setSpeed(s.variable[7]);
                        }
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

                            Online::getInstance()->setActive(false);
                        }

                        //check if was spectating him. If yes, kill the link
                        if(m_interface.getTarget()==player)
                            m_interface.setTarget(NULL);
                        if(m_camera.getCible()==player)
                            m_camera.setCible(NULL);


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
                            m_map.getPhase()->sendPatternOnline(s.variable[0]);
                        }
                        else
                        {
                            cerr<<"received pattern "<< s.text <<" from server!"<<endl;
                            m_map.getPhase()->addPatternToQueue(s.text,s.variable[1]);

                        }
                    }
                    //phase
                    if(s.type==9)
                    {
                        m_map.getPhase()->setName(s.text);
                        m_map.getPhase()->iniMap();
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
                        castSpell(player,"longjump");
                        //playPlayerSound(player,"../data/sounds/boost.wav");
                    }
                    //loot new spell
                    if(s.type==16)
                    {
                        int spellID=s.variable[1];
                        string spellName=Spell::idToName(spellID);

                        if(spellName=="jump")
                            player->addSpell(new SpellJump());
                        if(spellName=="longjump")
                            player->addSpell(new SpellLongJump());
                        if(spellName=="rope")
                            player->addSpell(new SpellRope());
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



bool Game::isMainPlayer(Player* p)
{
    if(playerList.size()>0 && p==playerList[0])
        return true;
    return false;
}
