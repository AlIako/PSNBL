#ifndef VIDEO_H_INCLUDED
#define VIDEO_H_INCLUDED
#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Fog.h"
#include "utilFunctions.h"
#include "Config.h"
#include "Vector3D.h"
#include "Tracer.h"
#include "Fade.h"

using namespace std;

class Video
{
    public:
    static Video* getInstance();

    void ini();
    void update(double functionTime);
    void close();

    GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

    Vector3D nextResolution(int width, int height);
    Vector3D previousResolution(int width, int height);

    void incrFOV(int i);

    void matrixProjection();
    void matrixOrtho2D();

    void beforeDraw();
    void afterDraw();

    string getStrHD();

    Fog* getFog() {return &fog;}
    Fade* getFade() {return &fade;}

    double getWidth() { return m_largeur; }
    double getHeight() {return m_hauteur;}

    ~Video();


    GLuint programID;
    GLuint programIDRed;
    GLuint programIDBlur;
    GLuint programIDWave;
    GLuint programIDText;

    private:
    Video();
    static Video* m_instance;


    double m_largeur;
    double m_hauteur;
    bool m_fullscreen;
    int m_fov;//field of view

    Fog fog;
    Fade fade;

    bool m_hd;

    vector<Vector3D> m_resolutions;
};

#endif // VIDEO_H_INCLUDED
