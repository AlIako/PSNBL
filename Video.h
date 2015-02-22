#ifndef VIDEO_H_INCLUDED
#define VIDEO_H_INCLUDED
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <fstream>
#include <iostream>
#include "Fog.h"

using namespace std;

class Video
{
    public:
    static Video* getInstance();

    void ini();
    void update(double functionTime);
    void close();

    void beforeDraw();
    void afterDraw();

    Fog* getFog() {return &fog;}

    double getWidth() { return m_largeur; }
    double getHeight() {return m_hauteur;}

    ~Video();

    private:
    Video();
    static Video* m_instance;


    double m_largeur;
    double m_hauteur;
    bool m_fullscreen;
    int m_fov;//field of view

    Fog fog;
};

#endif // VIDEO_H_INCLUDED
