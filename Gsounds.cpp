#include "Gsounds.h"


Gsounds::Gsounds()
{
    on=false;
    music=false;
}


void Gsounds::initialiser()
{
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 32, FMOD_INIT_3D_RIGHTHANDED, NULL);
    FMOD_System_Set3DSettings(system,1.0f, 1.0f, 1.0f);

    for(unsigned int i=0;i<sounds.size();i++)
        if(sounds[i]->getType()=="music")
            sounds[i]->pause(music);
        else sounds[i]->pause(on);
}

void Gsounds::reinitialiser()
{
    fermer();
    initialiser();
}
void Gsounds::play(std::string nom)
{
    /*FMOD_CHANNELGROUP *canal;
    FMOD_System_GetMasterChannelGroup(system, &canal);
    FMOD_ChannelGroup_SetVolume(canal,0.1);*/
    for(unsigned int i=0;i<sounds.size();i++)
        if(sounds[i]!=NULL && sounds[i]->getChemin()==nom )
            if(on || sounds[i]->getType()!="son")
            {
                sounds[i]->play();
                if(sounds[i]->getType()=="music" && !music)
                    sounds[i]->pause(music);
            }
    //FMOD_System_Update(system);
}
void Gsounds::play(std::string nom, int rel,int dmin, int dmax)
{
    /*FMOD_CHANNELGROUP *canal;
    FMOD_System_GetMasterChannelGroup(system, &canal);
    FMOD_ChannelGroup_SetVolume(canal,0.1);*/
    for(unsigned int i=0;i<sounds.size();i++)
        if(sounds[i]!=NULL && sounds[i]->getChemin()==nom )
            if(on || sounds[i]->getType()!="son")
                sounds[i]->play(rel,dmin,dmax);
    //FMOD_System_Update(system);
}
void Gsounds::update(Vector3D listener,Vector3D velocity,Vector3D forward,Vector3D up)
{

    listenerp.x=listener.X;
    listenerp.y=listener.Y;
    listenerp.z=listener.Z;

    velocityp.x=velocity.X;
    velocityp.y=velocity.Y;
    velocityp.z=velocity.Z;

    forwardp.x=forward.X;
    forwardp.y=forward.Y;
    forwardp.z=forward.Z;

    upp.x=up.X;
    upp.y=up.Y;
    upp.z=up.Z;
    FMOD_System_Set3DListenerAttributes(system,0, &listenerp, 0, &forwardp, &upp);
    FMOD_System_Update(system);

}
void Gsounds::volume(std::string nom, float v)
{
    for(unsigned int i=0;i<sounds.size();i++)
    {
        if(sounds[i]!=NULL && sounds[i]->getChemin()==nom)
            sounds[i]->volume(v);
    }
}

void Gsounds::loads()
{
    addSound("data/sounds/jump1.wav");
    addSound("data/sounds/jump2.wav");
    addSound("data/sounds/hurt.wav");
    addSound("data/sounds/lilian_die.wav");
    addSound("data/sounds/lilian_punch.wav");
    addSound("data/sounds/lilian_punch2.wav");
    addSound("data/sounds/lilian_punch3.wav");
    addSound("data/sounds/rollo_turbo.wav");
    addSound("data/sounds/rollo_attack.wav");
    addSound("data/sounds/rolloG_attack.wav");
    addSound("data/sounds/rolloG_attack2.wav");
    addSound("data/sounds/nova.wav");
    addSound("data/sounds/bubble.wav");
    addSound("data/sounds/tremblement.wav");


    addSound("data/sounds/sifflement.wav");
    addSound("data/sounds/sifflement2.wav");


    addSound("data/sounds/bonus.mp3");
    addSound("data/sounds/rubis.wav");
    addSound("data/sounds/secret.wav");
    addSound("data/sounds/bonusnova.wav");
    addSound("data/sounds/reload.wav");
    addSound("data/sounds/bonusboost.wav");
    addSound("data/sounds/button.wav");
    addSound("data/sounds/mechanic.wav");
    addSound("data/sounds/mechanic2s.wav");
    addSound("data/sounds/champi.wav");
    addSound("data/sounds/goutte.wav");
    addSound("data/sounds/futuristic_wave.mp3");
    addSound("data/sounds/glow1.wav");
    addSound("data/sounds/glow2.wav");
    addSound("data/sounds/vie.wav");

    addSound("data/sounds/explosion.wav");
    addSound("data/sounds/explosion1.wav");

    addSound("data/sounds/walkdirt1.wav");
    addSound("data/sounds/walkdirt2.wav");
    addSound("data/sounds/walkdirt3.wav");
    addSound("data/sounds/walkdirt4.wav");

    addSound("data/sounds/walkwood1.wav");
    addSound("data/sounds/walkwood2.wav");

    addSound("data/sounds/walkrock1.wav");
    addSound("data/sounds/walkrock2.wav");

    addSound("data/sounds/walkmetal1.wav");
    addSound("data/sounds/walkmetal2.wav");

    addSound("data/sounds/walkwater1.wav");
    addSound("data/sounds/walkwater2.wav");

    addSound("data/sounds/swimwater1.wav");

    addSound("data/sounds/watermove.wav");

    addSound("data/sounds/bouton.wav");
    addSound("data/sounds/back.wav");
    addSound("data/sounds/cursor.wav");
    addSound("data/sounds/chat.wav");


    addSound("data/sounds/forest.wav");
    addSound("data/sounds/water.wav");
    addSound("data/sounds/acqua.wav");
    addSound("data/sounds/eau.wav");
    addSound("data/sounds/world_gate.wav");
    addSound("data/sounds/beach.mp3");
    addSound("data/sounds/seagull.mp3");
    addSound("data/sounds/OOT_Fire.wav");



    addSound("data/sounds/gate_open.wav");
    addSound("data/sounds/mushroom.wav");

    addSound("data/sounds/monstre_hurt.wav");
    addSound("data/sounds/monstre_hurt2.wav");
    addSound("data/sounds/monstre_die.wav");
    addSound("data/sounds/monstre_pull.wav");
    addSound("data/sounds/zombie_die.wav");
    addSound("data/sounds/zombie_attack.wav");
    addSound("data/sounds/zombie_groan.wav");
    addSound("data/sounds/zombie_groan2.wav");

    addSound("data/sounds/bird_hurt.wav");
    addSound("data/sounds/bird_die.wav");

    addSound("data/sounds/slimjump.wav");
    addSound("data/sounds/bounce.wav");
}

void Gsounds::addSound(std::string chemin)
{
    bool found=false;
    for(unsigned int i=0;i<sounds.size();i++)
        if(chemin==sounds[i]->getChemin())
            found=true;
    if(!found)
    {
        sounds.push_back(new Sound());
        sounds[sounds.size()-1]->loadSound(chemin,system);
    }
}

void Gsounds::addMusic(std::string chemin)
{
    bool found=false;
    for(unsigned int i=0;i<sounds.size();i++)
        if(chemin==sounds[i]->getChemin())
        {
            found=true;
            sounds[i]->pause(false);
            sounds[i]->free();
            for(unsigned int j=i;j<sounds.size()-1;j++)
                sounds[j]=sounds[j+1];
            sounds.pop_back();

        }
    if(!found || 1)
    {
        sounds.push_back(new Sound());
        sounds[sounds.size()-1]->loadMusic(chemin,system);
    }
}

void Gsounds::pauseSounds(bool p)
{
    for(unsigned int i=0;i<sounds.size();i++)
        if(sounds[i]->getType()=="son")
            sounds[i]->pause((int)p);
}
void Gsounds::pauseMusic(bool p)
{
    for(unsigned int i=0;i<sounds.size();i++)
        if(sounds[i]->getType()=="music")
            sounds[i]->pause((int)p);
}
Sound* Gsounds::getSound(std::string chemin)
{
    for(unsigned int i=0;i<sounds.size();i++)
        if(chemin==sounds[i]->getChemin())
            return sounds[i];
    return NULL;
}
void Gsounds::freeSound(std::string chemin)
{
    bool found=false;
    for(unsigned int i=0;i<sounds.size() && !found;i++)
    {
        if(sounds[i]->getChemin()==chemin)
        {
            sounds[i]->free();
            delete sounds[i];
            sounds[i]=NULL;
            for(unsigned int j=i;j<sounds.size()-1;j++)
                sounds[j]=sounds[j+1];
            sounds.pop_back();
            found=true;
        }
    }
}
void Gsounds::stopMusic()
{
    for(unsigned int i=0;i<sounds.size();i++)
    {
        if(sounds[i]->getType()=="music")
        {
            sounds[i]->free();
            delete sounds[i];
            sounds[i]=NULL;
            for(unsigned int j=i;j<sounds.size()-1;j++)
                sounds[j]=sounds[j+1];
            sounds.pop_back();
        }
    }
}
void Gsounds::freeAll()
{
    for(unsigned int i=0;i<sounds.size();i++)
        sounds[i]->free();
    sounds.clear();
}

void Gsounds::fermer()
{
    freeAll();
    FMOD_System_Close(system);
    FMOD_System_Release(system);
}

void Gsounds::active(bool a)
{
    on=a;
    if(!on)
    {
        FMOD_CHANNELGROUP *canal;
        FMOD_System_GetMasterChannelGroup(system, &canal);
        FMOD_ChannelGroup_SetVolume(canal,0);//FAIL
    }
}
void Gsounds::activeZik(bool a)
{
    music=a;
}
void Gsounds::save()
{
	//load
    ifstream fichier1("settings.txt", ios::in);
    int la=640, ha=480, fu=0, an=0;
    string host="";
    int sound=0, zik=0;
    if(fichier1)
    {
        fichier1 >> la >> ha >> fu >> an >> sound >> zik;
        fichier1.close();
    }
    else
        cerr << "can't open settings file" << endl;
    fichier1.close();
	//save
	char* tempchemin=stringtochar("settings.txt");
    ofstream fichier(tempchemin, ios::out | ios::trunc);
    delete tempchemin;
    tempchemin=NULL;

    fichier <<  la << " " << ha << " " << fu << " " << an << " " << on << " " << music;
    fichier.close();

}




