#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include "Object.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <SDL.h>
#include <SDL/SDL_image.h>
#include "sdlglutils.h"

enum DIRECTION { DOWN, LEFT, UP, RIGHT };

class Personnage: public Object
{
    public:
    Personnage();
    void loadSprite();
    virtual void ini();
    virtual void draw();

    void pressKey(DIRECTION k, bool pressed);
    void handlePressedKeys();


    void move(int);
    void addAngle(int);
    void calculDirector();

    virtual ~Personnage();

    protected:
    double m_dx, m_dy;
    bool m_pressed[4];
    double speed;
    Texture* m_texture;
};

#endif // PERSONNAGE_H
