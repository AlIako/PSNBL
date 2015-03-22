#ifndef LAVA_H_INCLUDED
#define LAVA_H_INCLUDED
#include "Bubble.h"

class Lava: public Object
{
    public:
    Lava();

    virtual void ini();
    virtual void update(double functionTime);
    virtual void draw();
    virtual void drawBlur();

    virtual void action(int type, Object* o=NULL);
    GLuint EmptyTexture();

    private:
    vector<Bubble> m_bubbles;
    vector<Bubble> m_steam;
    double mosaic;

    Vector3D txtcord;

    DRDampingSpring dampvalue;

    string loopSound;
    GTime loopSoundTime;
    int nextLoopSoundTime;

    string bubbleSound;
    GTime bubbleSoundTime;
    int nextBubbleSoundTime;

    //blur
    GLuint BlurTexture;
};
#endif // LAVA_H_INCLUDED
