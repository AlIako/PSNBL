#ifndef FADE_H_INCLUDED
#define FADE_H_INCLUDED
#include <SDL.h>
#include <GL/glew.h>
#include "GTexture.h"
#include "Lighting.h"

class Fade
{
    public:
    Fade();
    void ini();
    void draw();
    void update(double functionTime);

    void startFadeIn();
    void startFadeOut();


    //set
    void setR(int r){m_r=r;}
    void setG(int g){m_g=g;}
    void setB(int b){m_b=b;}
    //get
    bool getFading() {return m_fading;}
    bool getFadingIn() {return m_fadingIn;}
    double getAlpha(){return m_alpha;}
    int getR(){return m_r;}
    int getG(){return m_g;}
    int getB(){return m_b;}

    private:
    int m_r;
    int m_g;
    int m_b;

    double m_alpha;

    bool m_fading;
    bool m_fadingIn;//false -> fading out
};


#endif // FADE_H_INCLUDED
