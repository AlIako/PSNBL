#include "Config.h"

Config* Config::m_instance = new Config();


Config* Config::getInstance()
{
    return m_instance;
}




Config::Config()
{
    mode="server";//server, client
    name="Linko";//online name
    ip="127.0.0.1";
    port=7777;
    protocol="udp";//udp tcp
    width=1152;
    height=864;
    fullscreen=false;
    fov=90;
    sound=false;
    music=false;
    editorpath="patterns";
}



void Config::save()
{
    ofstream fichier("config.ini", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

    fichier << "mode: "<< mode<<endl;
    fichier << "name: "<< name<<endl;
    fichier << "ip: "<< ip<<endl;
    fichier << "port: "<< port<<endl;
    fichier << "protocol: "<< protocol<<endl;
    fichier << "resolution: "<< width <<" " << height <<endl;
    fichier << "fullscreen: "<< fullscreen<<endl;
    fichier << "fov: "<< fov<<endl;
    fichier << "sound: "<< sound<<endl;
    fichier << "music: "<< music<<endl;
    fichier << "editorpath: "<< editorpath<<endl;

    fichier.close();
}


void Config::load()
{
    std::ifstream file("config.ini", std::ios::in);

    if(file)
    {
        std::string befor_read="",read_name="",read_name_before="";
        std::string cur_read="";
        int cur_int=0;

        while(!file.eof())
        {
            read_name=cur_read.substr(0,cur_read.size()-1);//enleve le ":"

            if(read_name_before=="mode")
            {
                file >> mode;
            }
            else if(read_name_before=="name")
            {
                file >> name;
            }
            else if(read_name_before=="port")
            {
                file >> port;
            }
            else if(read_name_before=="protocol")
            {
                file >> protocol;
            }
            else if(read_name_before=="resolution")
            {
                file >> cur_int;
                width=cur_int;
                file >> cur_int;
                height=cur_int;
            }
            else if(read_name=="fullscreen")
            {
                file >> cur_int;
                if(cur_int)
                    fullscreen=true;
                else fullscreen=false;
            }
            else if(read_name=="fov")
            {
                file >> cur_int;
                fov=cur_int;
            }
            else if(read_name_before=="sound")
            {
                file >> cur_int;
                if(cur_int)
                    sound=true;
                else sound=false;
            }
            else if(read_name_before=="music")
            {
                file >> cur_int;
                if(cur_int)
                    music=true;
                else music=false;
            }
            else if(read_name_before=="editorpath")
            {
                file >> editorpath;
            }

            file >> cur_read;
            befor_read=cur_read;
            read_name_before=befor_read.substr(0,befor_read.size()-1);//enleve le ":"

        }

        std::cerr<<std::endl;
        file.close();
    }
    else
        std::cerr << "can't open file (config settings)" << std::endl;
}

void Config::toggleFullscreen()
{
    if(fullscreen)
        fullscreen=false;
    else fullscreen=true;
}

void Config::toggleSound()
{
    if(sound)
        sound=false;
    else sound=true;
}

void Config::toggleMusic()
{
    if(music)
        music=false;
    else music=true;
}



