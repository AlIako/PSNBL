#include "Gsounds.h"


Gsounds* Gsounds::m_instance = new Gsounds();


Gsounds* Gsounds::getInstance()
{
    return m_instance;
}



Gsounds::Gsounds()
{
    on=false;
    music=false;
}


void Gsounds::ini()
{
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 32, FMOD_INIT_3D_RIGHTHANDED, NULL);
    FMOD_System_Set3DSettings(system,1.0f, 1.0f, 1.0f);

    for(unsigned int i=0;i<sounds.size();i++)
        if(sounds[i]->getType()=="music")
            sounds[i]->pause(music);
        else sounds[i]->pause(on);



    music=Config::getInstance()->music;
    on=Config::getInstance()->sound;
}

void Gsounds::reini()
{
    close();
    ini();
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
                cerr<<"playn"<<endl;
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
    addSound("../data/sounds/boost.wav");
    addSound("../data/sounds/bounce.wav");
    addSound("../data/sounds/chat.wav");
    addSound("../data/sounds/explosion.wav");
    addSound("../data/sounds/health.wav");
    addSound("../data/sounds/lava_loop.mp3");
    addSound("../data/sounds/lavabubble.wav");
    addSound("../data/sounds/fire.mp3");
    addSound("../data/sounds/metal_impact.mp3");

    addSound("../data/sounds/walkdirt1.wav");
    addSound("../data/sounds/walkdirt2.wav");
    addSound("../data/sounds/walkdirt3.wav");
    addSound("../data/sounds/walkdirt4.wav");

    addSound("../data/sounds/walkwood1.wav");
    addSound("../data/sounds/walkwood2.wav");

    addSound("../data/sounds/walkrock1.wav");
    addSound("../data/sounds/walkrock2.wav");

    addSound("../data/sounds/walkmetal1.wav");
    addSound("../data/sounds/walkmetal2.wav");

    addSound("../data/sounds/walkwater1.wav");
    addSound("../data/sounds/walkwater2.wav");

    addSound("../data/sounds/jump1.wav");
    addSound("../data/sounds/jump2.wav");

    addSound("../data/sounds/hover.mp3");
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

            sounds.erase(sounds.begin()+i);

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
            sounds.erase(sounds.begin()+i);
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
            sounds.erase(sounds.begin()+i);
        }
    }
}
void Gsounds::freeAll()
{
    for(unsigned int i=0;i<sounds.size();i++)
        sounds[i]->free();
    sounds.clear();
}

void Gsounds::close()
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




