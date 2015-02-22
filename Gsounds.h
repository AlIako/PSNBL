#ifndef GSOUNDS_H_INCLUDED
#define GSOUNDS_H_INCLUDED
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Sound.h"
#include "utilFunctions.h"

class Gsounds
{
    public:
    Gsounds();
    void initialiser();
    void reinitialiser();
    void play(std::string nom);
    void play(std::string nom, int rel,int dmin, int dmax);
    void stopMusic();
    void volume(std::string nom, float v);
    void update(Vector3D listener,Vector3D velocity,Vector3D forward,Vector3D up);
    void loads();
    void addSound(std::string chemin);
    void addMusic(std::string chemin);
    void pauseSounds(bool p=true);
    void pauseMusic(bool p=true);
    Sound* getSound(string nom);
    void freeSound(std::string chemin);
    void freeAll();
    void fermer();
    void active(bool a);
    void activeZik(bool a);
    void save();

    bool on;
    bool music;
    private:
    FMOD_SYSTEM *system;
    std::vector<Sound*> sounds;
    FMOD_VECTOR listenerp;
    FMOD_VECTOR velocityp;
    FMOD_VECTOR forwardp;
    FMOD_VECTOR upp;
};

#endif // GSOUNDS_H_INCLUDED
