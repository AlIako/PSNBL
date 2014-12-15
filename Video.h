#ifndef VIDEO_H_INCLUDED
#define VIDEO_H_INCLUDED
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Video
{
    public:
    Video();
    void ini();
    void close();

    void beforeDraw();
    void afterDraw();

    ~Video();

    private:
    double m_largeur;
    double m_hauteur;
};

#endif // VIDEO_H_INCLUDED
