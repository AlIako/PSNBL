#include "Video.h"



Video::Video()
{

}



void Video::ini()
{
    m_largeur=800;
    m_hauteur=600;



    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetCaption("PSNBLAL 0.01",NULL);
    SDL_SetVideoMode(m_largeur, m_hauteur, 32, SDL_OPENGL);


    SDL_Init(SDL_INIT_VIDEO);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)m_hauteur/m_largeur,0.01,1000);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

  	glEnable(GL_DEPTH_TEST); 	// Active le test de profondeur

    SDL_ShowCursor(SDL_DISABLE);//no cursor
    SDL_WM_GrabInput(SDL_GRAB_ON);

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

