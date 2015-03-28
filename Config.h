#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Config
{
public:
    static Config* getInstance();
    void save();
    void load();

    void toggleFullscreen();
    void toggleSound();
    void toggleMusic();

    string mode;//server, client
    string name;//online name
    string ip;
    int port;
    string protocol;//udp tcp
    int width;
    int height;
    bool fullscreen;
    int fov;
    bool sound;
    bool music;

    string editorpath;

private:
    Config();
    static Config* m_instance;

};

#endif // CONFIG_H_INCLUDED
