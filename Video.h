#ifndef VIDEO_H_INCLUDED
#define VIDEO_H_INCLUDED
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Fog.h"


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


    ~Video();

    private:
    Video();
    static Video* m_instance;


    double m_largeur;
    double m_hauteur;

    Fog fog;
};

#endif // VIDEO_H_INCLUDED
