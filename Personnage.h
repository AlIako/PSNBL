#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <iostream>
#include <cmath>
#include <vector>
#include <SDL.h>
#include <SDL/SDL_image.h>
#include "sdlglutils.h"

enum DIRECTION { DOWN, LEFT, UP, RIGHT };

class Personnage
{
    public:
    Personnage();
    void loadSprite();
    void draw();

    void pressKey(DIRECTION k, bool pressed);
    void handlePressedKeys();


    void move(int);
    void addAngle(int);
    void calculDirector();



    void setPos(double x, double y)  {m_x=x; m_y=y;}
    void setAngle(double a)  {m_angle=floor(a);}

    double getX() {return m_x;}
    double getY() {return m_y;}
    double getAngle() {return m_angle;}


    virtual ~Personnage();

    protected:
    int m_angle;
    double m_x, m_y;
    double m_dx, m_dy;
    bool m_pressed[4];
    double speed;
    GLuint m_texture;
};

#endif // PERSONNAGE_H
