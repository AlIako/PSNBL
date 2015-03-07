#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED
#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <fmodex/fmod.h>
#include "Vector3D.h"
#include "Config.h"

using namespace std;

class Sound
{
    public:
    Sound();
    void loadSound(std::string chemin, FMOD_SYSTEM* sys);
    void loadMusic(std::string chemin, FMOD_SYSTEM* sys);
    void play();
    void play(int rel,int dmin, int dmax);
    void setPos(Vector3D v);
    int getLength();
    void pause(bool p=true);
    void volume(float v);
    void free();
    std::string getChemin();
    std::string getType();

    private:
    Vector3D m_position;
    std::string m_chemin;
    unsigned int length;
    bool loaded;
    FMOD_SOUND *son;
    FMOD_SYSTEM* system;
    FMOD_CHANNEL * channel;
    string m_type;
    FMOD_VECTOR position;
    FMOD_VECTOR velocity;
    bool paused;
};


#endif // SOUND_H_INCLUDED
