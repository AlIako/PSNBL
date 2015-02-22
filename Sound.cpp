#include "Sound.h"

#include <iostream>
#include "sdlglutils.h"
#include "utilFunctions.h"

Sound::Sound()
{
    loaded=false;
    m_chemin="";
    system=NULL;
    son=NULL;
    m_type="son";
    length=0;
    paused=false;
}

void Sound::loadSound(std::string chemin, FMOD_SYSTEM* sys)
{
    int tempsPrecedent=SDL_GetTicks();

    m_type="son";
    m_chemin=chemin;
    system=sys;

    char* tempchemin=stringtochar(chemin);
    FMOD_RESULT resultat = FMOD_System_CreateSound(system, tempchemin, FMOD_3D, 0, &son);
    delete tempchemin;
    tempchemin=NULL;

    if (resultat == FMOD_OK)
    {
        FMOD_Sound_GetLength(son,&length,FMOD_TIMEUNIT_MS);
        loaded=true;
        cerr << "Son " << chemin << ", " << length << "ms"<< "(" << SDL_GetTicks()-tempsPrecedent << "ms)." << endl;
    }
    else
        cerr << "Echec du chargement du son " << chemin << " !" << endl;
}
void Sound::loadMusic(std::string chemin, FMOD_SYSTEM* sys)
{
    int tempsPrecedent=SDL_GetTicks();

    m_type="music";
    m_chemin=chemin;
    system=sys;

    char* tempchemin=stringtochar(chemin);
    FMOD_RESULT resultat = FMOD_System_CreateSound(system, tempchemin, FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &son);
    delete tempchemin;
    tempchemin=NULL;

    if (resultat == FMOD_OK)
    {
        loaded=true;
        cerr << "Musique " << chemin << "(" << SDL_GetTicks()-tempsPrecedent << "ms)." << endl;
        FMOD_Sound_SetLoopCount(son, -1);
    }
    else
        cerr << "Echec du chargement de la musique " << chemin << " !" << endl;
}

void Sound::play()
{
    if(loaded && son!=NULL)
    {
        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, son, true, &channel);
        position.x=0;
        position.y=0;
        position.z=0;
        FMOD_Channel_Set3DAttributes(channel,&position, 0);
        FMOD_Channel_SetMode(channel, FMOD_3D_HEADRELATIVE);
        if(!paused)
            FMOD_Channel_SetPaused(channel,false);
    }
}
void Sound::play(int rel,int dmin, int dmax)
{
    if(loaded && son!=NULL)
    {
        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, son, true, &channel);
        FMOD_Channel_Set3DAttributes(channel,&position, 0);
        if(rel==0)
            FMOD_Channel_SetMode(channel, FMOD_3D_HEADRELATIVE);
        else
        {
            FMOD_Channel_SetMode(channel, FMOD_3D_WORLDRELATIVE);
            FMOD_Channel_SetMode(channel, FMOD_3D_LINEARROLLOFF);
            FMOD_Channel_Set3DMinMaxDistance(channel,dmin,dmax);
        }
        if(!paused)
            FMOD_Channel_SetPaused(channel,false);
    }
}
void Sound::setPos(Vector3D v)
{
    position.x=v.X;
    position.y=v.Y;
    position.z=v.Z;
    velocity.x=0;
    velocity.y=0;
    velocity.z=0;
    FMOD_Channel_Set3DAttributes(channel,&position, 0);
}
int Sound::getLength()
{
    return length;
}
void Sound::pause(bool p)
{
    /*if(m_type=="son")
    {
        FMOD_CHANNELGROUP *canal;
        FMOD_BOOL etat;
        FMOD_System_GetMasterChannelGroup(system, &canal);
        FMOD_ChannelGroup_GetPaused(canal, &etat);
        if(p!=-1)
            FMOD_ChannelGroup_SetPaused(canal,p);
        else if(etat==1)
            FMOD_ChannelGroup_SetPaused(canal,0);
        else
            FMOD_ChannelGroup_SetPaused(canal,1);

    }
    else if(m_type=="music")
    {
        FMOD_CHANNEL *canal;
        FMOD_System_GetChannel(system, 0, &canal);
        FMOD_BOOL etat;
        FMOD_Channel_GetPaused(canal, &etat);
        cerr<<"pausing music "<<m_chemin<<endl;
        FMOD_Channel_SetPaused (channel, p);
        if(p!=-1)
            FMOD_Channel_SetPaused(canal,p);
        else if(etat==1)
            FMOD_Channel_SetPaused(canal,0);
        else
            FMOD_Channel_SetPaused(canal,1);
    }*/
    FMOD_Channel_SetPaused (channel, !p);
    paused=!p;
}


void Sound::volume(float v)
{
    //FSOUND_SetVolume (son, v);
}


void Sound::free()
{
    loaded=false;
    FMOD_Sound_Release(son);
}
std::string Sound::getChemin()
{
    return m_chemin;
}

std::string Sound::getType()
{
    return m_type;
}
