#include "Game.h"


void Game::close()
{
    if(m_online->active())
    {
        infosSocket s;
        s.type=12;
        s.confirmationID=-1;
        m_online->sendSocket(s);
        SDL_Delay(250);

        m_online->closeOnline();
    }
    Video::getInstance()->getFog()->close();

    Interface::getInstance()->close();
    Lighting::getInstance()->delAll();

    Map::getInstance()->erase();
    Gsounds::getInstance()->freeAll();

    cerr<<"Exited cleanly."<<endl<<endl<<endl;
}

bool Game::checkEndLevel()
{
    bool result=false;

    if(!(playerList.size()>0 && playerList[0]->getLife()>0))
        return false;

    std::vector<Object*>* objects=Map::getInstance()->getObjects();
    for(int i=0;i<(int)objects->size();i++)
    {
        if((*objects)[i]->getType()=="endlevel")
        {
            if((*objects)[i]->collision(playerList[0]))
                result=true;
            break;
        }
    }
    return result;
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
            if(!Online::getInstance()->active() || Online::getInstance()->inControl())
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
        else if(c=="/noclip")
        {
            playerList[0]->setTestMode(true);
            m_chat.recieveMessage("Noclip activated.",0,-2);
        }
        else if(c=="/noclipoff")
        {
            playerList[0]->setTestMode(false);
            m_chat.recieveMessage("Noclip deactivated.",0,-2);
        }
        else if(c=="/lava" || c=="/lavapos")
        {
            //command not found
            stringstream ss;
            ss << "Lava Z is "<<Map::getInstance()->getLavaLevel();
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
                    s->resetCooldown();
                    p->linkRope(Map::getInstance()->createRope(p->getPos(),param1));

                    playPlayerSound(p,"../data/sounds/bounce.wav");

                    return true;
                }
                else if(s->getName()=="jump")
                {
                    if(p->jump())
                    {
                        s->resetCooldown();
                        return true;
                    }
                }
                else if(s->getName()=="longjump")
                {
                    if(!isMainPlayer(p) || p->jump())
                    {
                        p->setVel(p->getVel()+p->getDir()/3.0);

                        s->resetCooldown();

                        playPlayerSound(p,"../data/sounds/boost.wav");

                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Game::updateCamMode()
{
    if(m_camera.getCible()!=NULL)
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
            Interface::getInstance()->setTarget(pTarget);
        }
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
        if(p && playerList[i]->getIdOnline()==p->getIdOnline())
            id=i;
    }

    //find next player in list that has no same id
    bool foundPl=false;
    for(unsigned int i=id, count=playerList.size();i<count;i++)
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
    Interface::getInstance()->setTarget(pTarget);
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
