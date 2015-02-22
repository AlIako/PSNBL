#include "Video.h"

Video* Video::m_instance = new Video();


Video* Video::getInstance()
{
    return m_instance;
}



Video::Video()
{

}



void Video::ini()
{
    m_largeur=800;
    m_hauteur=600;
    m_fullscreen=false;
    m_fov=90;

    ifstream file("config.ini", ios::in);

    if(file)
    {
        std::string befor_read="",read_name="",read_name_before="";
        std::string cur_read="";
        int cur_int=0;

        while(!file.eof())
        {
            read_name=cur_read.substr(0,cur_read.size()-1);//enleve le ":"

            if(read_name_before=="resolution")
            {
                file >> cur_int;
                m_largeur=cur_int;
                file >> cur_int;
                m_hauteur=cur_int;

                cerr<<"resolution: "<<m_largeur<<" "<< m_hauteur<<endl;
            }
            else if(read_name=="fullscreen")
            {
                file >> cur_int;
                if(cur_int)
                    m_fullscreen=true;
                else m_fullscreen=false;
            }
            else if(read_name=="fov")
            {
                file >> cur_int;
                m_fov=cur_int;
            }

            file >> cur_read;
            befor_read=cur_read;
            read_name_before=befor_read.substr(0,befor_read.size()-1);//enleve le ":"

        }

        cerr<<endl;
        file.close();
    }
    else
        cerr << "can't open file (config settings)" << endl;




    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetCaption("PSNBLAL 0.06",NULL);

    if(m_fullscreen)
        SDL_SetVideoMode(m_largeur, m_hauteur, 32, SDL_OPENGL | SDL_FULLSCREEN);
    else SDL_SetVideoMode(m_largeur, m_hauteur, 32, SDL_OPENGL);

    SDL_Init(SDL_INIT_VIDEO);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(m_fov,(double)m_hauteur/m_largeur,0.01,1000);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

  	glEnable(GL_DEPTH_TEST); 	// Active le test de profondeur

    SDL_ShowCursor(SDL_DISABLE);//no cursor
    SDL_WM_GrabInput(SDL_GRAB_ON);


    fog.enable();
}

void Video::update(double functionTime)
{
    fog.update(functionTime);
}

void Video::beforeDraw()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
}

void Video::afterDraw()
{
    glFlush();
    SDL_GL_SwapBuffers();
}









void Video::close()
{
    SDL_Quit();
}

Video::~Video()
{

}

