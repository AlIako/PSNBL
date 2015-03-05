#include "Editor.h"
Editor::Editor()
{
}


void Editor::ini()
{
    m_fps=0;
    m_fpsTime.reset();

    grabCursor=true;

    //video
    m_video=Video::getInstance();
    m_video->ini();

    m_camera.setDist(15);

    //sound
    Gsounds::getInstance()->ini();
    Gsounds::getInstance()->loads();


    //interface
    m_interface.ini();

    m_map.createWalls();
    m_map.loadPat("../data/patterns/newPat.txt");

    posCur=Vector3D(0,0,0);
    curObj=new Block();
    curObj->ini();
    curObj->setPos(Vector3D(0,0,0));
    curObj->setSize(Vector3D(1,1,1));


    m_camera.setCible(curObj);
    m_camera.setMode("editor");

}


void Editor::play()
{
    ini();

    SDL_EnableKeyRepeat(20, 20);

    SDL_Event event;

    playLoop=true;

    double cur_incr=0.5;
    showCur=true;

    while (playLoop)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                playLoop = false;
                break;

                case SDL_MOUSEMOTION:
                m_camera.onMouseMotion(event.motion);
                break;

                case SDL_MOUSEBUTTONUP:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    m_map.getObjects()->push_back(curObj);
                    Object* lastObj=curObj;
                    curObj=new Block();
                    curObj->ini();
                    curObj->setPos(lastObj->getPos());
                    curObj->setSize(lastObj->getSize());
                    m_camera.setCible(curObj);
                }
                if(event.button.button==SDL_BUTTON_RIGHT)
                {
                }
                else if(event.button.button==SDL_BUTTON_WHEELUP)
                    m_camera.zoom(0.7);
                else if(event.button.button==SDL_BUTTON_WHEELDOWN)
                    m_camera.zoom(-0.7);
                break;

                case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_KP_ENTER:
                    break;
                    case SDLK_RETURN:
                    break;
                    case SDLK_a:
                        moveObj(Vector3D(-1,0,0));
                    break;
                    case SDLK_d:
                        moveObj(Vector3D(1,0,0));
                    break;
                    case SDLK_w:
                        moveObj(Vector3D(0,1,0));
                    break;
                    case SDLK_s:
                        moveObj(Vector3D(0,-1,0));
                    break;
                    case SDLK_e:
                        moveObj(Vector3D(0,0,1));
                    break;
                    case SDLK_q:
                        moveObj(Vector3D(0,0,-1));
                    break;
                    case SDLK_SPACE:
                    break;
                    case SDLK_ESCAPE:
                    playLoop = false;
                    break;

                    case SDLK_LSHIFT:
                    break;
                    default:
                    break;
                }
                break;

                case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_KP_ENTER:
                    break;
                    case SDLK_RETURN:
                        m_map.saveMap("../data/patterns/newPat.txt");
                    break;
                    case SDLK_BACKSPACE:
                        m_map.deleteLastObj();
                    break;
                    case SDLK_a:
                    break;
                    case SDLK_d:
                    break;
                    case SDLK_w:
                    break;
                    case SDLK_s:
                    break;
                    case SDLK_e:
                    break;
                    case SDLK_r:
                    break;
                    case SDLK_f:
                        if(showCur)
                            showCur=false;
                        else showCur=true;
                    break;
                    case SDLK_t:
                        curObj->setSize(Vector3D(curObj->getSize().X+cur_incr,curObj->getSize().Y,curObj->getSize().Z));
                    break;
                    case SDLK_y:
                        curObj->setSize(Vector3D(curObj->getSize().X,curObj->getSize().Y+cur_incr,curObj->getSize().Z));
                    break;
                    case SDLK_u:
                        curObj->setSize(Vector3D(curObj->getSize().X,curObj->getSize().Y,curObj->getSize().Z+cur_incr));
                    break;
                    case SDLK_h:
                        curObj->setSize(Vector3D(curObj->getSize().X-cur_incr,curObj->getSize().Y,curObj->getSize().Z));
                    break;
                    case SDLK_j:
                        curObj->setSize(Vector3D(curObj->getSize().X,curObj->getSize().Y-cur_incr,curObj->getSize().Z));
                    break;
                    case SDLK_k:
                        curObj->setSize(Vector3D(curObj->getSize().X,curObj->getSize().Y,curObj->getSize().Z-cur_incr));
                    break;
                    case SDLK_UP:
                    cur_incr*=2.0;
                    break;
                    case SDLK_DOWN:
                    cur_incr/=2.0;
                    break;
                    case SDLK_c:
                    if(grabCursor)
                    {
                        SDL_ShowCursor(SDL_ENABLE);//pas de curseur
                        SDL_WM_GrabInput(SDL_GRAB_OFF);
                        grabCursor=false;
                    }
                    else
                    {
                        SDL_ShowCursor(SDL_DISABLE);//pas de curseur
                        SDL_WM_GrabInput(SDL_GRAB_ON);
                        grabCursor=true;
                    }
                    break;
                    case SDLK_LSHIFT:
                    break;
                    default:
                    break;
                }
                break;
            }
        }

        //update stuff
        updateTimes();

        Gsounds::getInstance()->update(m_camera.getPos().toLeft(),Vector3D(0,0,0),m_camera.getDir().toLeft(),Vector3D(0,0,1));

        m_video->update(ft);

        m_interface.update(ft);

        //draw
        m_video->beforeDraw();

        m_camera.look();

        m_map.draw();

        if(showCur)
            curObj->draw();

        //m_interface.draw();


        m_video->afterDraw();

        //fps calcul
        m_fps++;
        m_fpsTime.couler();
        if(m_fpsTime.ecouler(1000))
        {
            m_interface.setFPS(m_fps);
            m_fps=0;
            m_fpsTime.reset();
        }

        SDL_Delay(10);
    }


    close();
}

void Editor::updateTimes()
{
    since_last_frame.couler();
    int timePast=since_last_frame.timePast();
    ft=timePast/15.000;//facteur temps(déplacement en fonction du temps)
    if(ft>1)
        ft=1;
    else if(ft<-1)
        ft=-1;

    m_camera.updateTime(ft);

    since_last_frame.reset();
}



void Editor::moveObj(Vector3D key)
{
    Vector3D dir=m_camera.getDir();
    Vector3D newPos=posCur;

    double speed=1;
    if(key.Y==1)//up
    {
        newPos.X+=speed*dir.X;
        newPos.Y+=speed*dir.Y;
    }
    if(key.Y==-1)//down
    {
        newPos.X-=speed*dir.X;
        newPos.Y-=speed*dir.Y;
    }
    if(key.X==1)//right
    {
        newPos.X+=dir.Y*speed;
        newPos.Y-=dir.X*speed;
    }
    if(key.X==-1)//left
    {
        newPos.X-=dir.Y*speed;
        newPos.Y+=dir.X*speed;
    }
    if(key.Z==1)//right
        newPos.Z+=speed;
    if(key.Z==-1)//left
        newPos.Z-=speed;

    posCur=newPos;
    curObj->setPos(Vector3D(floor(posCur.X),floor(posCur.Y),floor(posCur.Z)));
}




void Editor::close()
{
    Gsounds::getInstance()->close();
    m_video->close();

    cerr<<"Exited cleanly.";
}


Editor::~Editor()
{

}




