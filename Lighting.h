#ifndef LIGHTING_H_INCLUDED
#define LIGHTING_H_INCLUDED
#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <string>
#include "utilFunctions.h"

using namespace std;

struct Light
{
    double x;
    double y;
    double z;
    double alpha;
    double at;
    int cible;
    int r;
    int g;
    int b;
    bool on;
};

class Lighting
{
    public:
    static Lighting* getInstance();

    void shineAmbiant();
    void shineAll();
    void addLight();
    Light getLight(unsigned int id);
    unsigned int getSize();
    void setX(string lequel,double x);
    void setY(string lequel,double y);
    void setZ(string lequel,double z);
    void setR(string lequel,double r);
    void setG(string lequel,double g);
    void setB(string lequel,double b);
    void setAT(string lequel,double at);
    void delAll();

    void glDisableLighting();
    void glEnableLighting();

    void setActive(bool a){m_active=a;}
    bool isActive(){return m_active;}

    private:
    Lighting();
    static Lighting* m_instance;

    vector <Light> lumieres;
    bool m_active;

};


#endif // LIGHTING_H_INCLUDED
