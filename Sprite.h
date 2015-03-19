#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED
#include <string>
#include "utilFunctions.h"
#include "Texture.h"
#include "GTime.h"
#include "Vector3D.h"

using namespace std;

class Sprite
{
    public:
    Sprite();
    void loadSprite(string chemin);
    void update();
    void display();
    string getChemin();
    void setPositions(Vector3D campos, Vector3D pos);
    bool getGoRota();
    void setGoRota(bool r);
    void setTaille(Vector3D t);
    Vector3D getTaille();

    private:
    std::vector<Texture*> m_frames;
    double m_vitesse;
    int m_current_frame;
    GTime m_nextFrame;
    Vector3D m_taille;
    string m_chemin;
    Vector3D m_camerapos;
    double angleZ;
    bool goRota;
};

#endif // SPRITE_H_INCLUDED
