#include "Editor.h"
Editor::Editor()
{
}

void Editor::handleTracer()
{
    //traces
    vector<Trace*>* traces=Tracer::getInstance()->getTraces();
    if(traces->size()>0)
    {
        for(unsigned int i=0;i<traces->size();i++)
        {
            if(!(*traces)[i]->sent)
            {
                (*traces)[i]->sent=true;
                m_chat.newMessage((*traces)[i]->msg,-1);
            }
        }
        Tracer::getInstance()->afterFetch();
    }
}

void Editor::ini(string path)
{
    m_path=path;
    m_fps=0;
    m_fpsTime.reset();

    grabCursor=true;

    //video
    m_video=Video::getInstance();
    //SDL_ShowCursor(SDL_DISABLE);//no cursor
    //SDL_WM_GrabInput(SDL_GRAB_ON);

    m_camera.setDist(15);

    Tracer::getInstance()->enable();
    //sound
    Gsounds::getInstance()->loads();

    //chat
    m_chat.activate(m_video->getWidth(), m_video->getHeight(), "../data/fonts/arial.TTF");
    m_chat.setSide(0);

    //map
    Map::getInstance()->createWalls();
    Map::getInstance()->translateAll(Vector3D(0,0,-15));
    Map::getInstance()->loadPat(path);
    Map::getInstance()->editor_on=true;

    posCur=Vector3D(0,0,0);
    curObj=new Block();
    curObj->ini();
    curObj->setPos(posCur);
    curObj->setSize(Vector3D(1,1,1));


    m_camera.setCible(curObj);
    m_camera.setMode("editor");

    Lighting* l=Lighting::getInstance();
    l->setActive(true);
    l->shineAmbiant();


    m_objects=Map::getInstance()->getObjects();


    m_video->getFade()->startFadeOut();

}


void Editor::play(string path)
{
    m_path=path;
    ini(path);

    SDL_EnableKeyRepeat(20, 20);

    SDL_Event event;

    playLoop=true;
    fadingToLeave=false;

    double cur_incr=0.5;
    showCur=true;

    while (playLoop)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                fadingToLeave=true;
                break;

                case SDL_MOUSEMOTION:
                if(interaction.appuye())
                    m_camera.onMouseMotion(event.motion);
                break;

                case SDL_MOUSEBUTTONUP:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    SDL_ShowCursor(SDL_ENABLE);
                    SDL_WM_GrabInput(SDL_GRAB_OFF);
                    if(justgrab)
                        justgrab=false;
                    else
                    {
                        //appuyer sur interface n shit
                    }
                    interaction.clickGauche(false,event.button.x,event.button.y);
                    if(!interaction.grab() && interaction.clicked() && playLoop/* && !touchebouton*/)
                        pick(event.button.x,event.button.y);
                    /*Map::getInstance()->getObjects()->push_back(curObj);
                    Object* lastObj=curObj;
                    curObj=new Block();
                    curObj->setPos(lastObj->getPos());
                    curObj->setSize(lastObj->getSize());
                    curObj->setName(lastObj->getName());
                    curObj->ini();
                    m_camera.setCible(curObj);*/
                }
                if(event.button.button==SDL_BUTTON_RIGHT)
                {
                }
                else if(event.button.button==SDL_BUTTON_WHEELUP)
                    m_camera.zoom(0.7);
                else if(event.button.button==SDL_BUTTON_WHEELDOWN)
                    m_camera.zoom(-0.7);
                break;
                case SDL_MOUSEBUTTONDOWN:
                if(1)
                {
                    bool surbutton=false;
                    /*for(unsigned int i=0;i<interf_editor.size() && !surbutton;i++)
                        if(interf_editor[i].click(event.button.x,event.button.y))
                            surbutton=true;*/
                    if(!surbutton)
                    {
                        interaction.clickGauche(true,event.button.x,event.button.y);
                        SDL_ShowCursor(SDL_DISABLE);//pas de curseur
                        SDL_WM_GrabInput(SDL_GRAB_ON);
                        justgrab=true;
                    }
                }
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
                    case SDLK_ESCAPE:
                    fadingToLeave=true;
                    break;
                    case SDLK_RETURN:
                        Map::getInstance()->saveMap(m_path);
                    break;
                    case SDLK_BACKSPACE:
                        Map::getInstance()->deleteLastObj();
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
                    if(1)//if I dont do that, compiler gives error... WTF?
                    {
                        string curType=curObj->getType();
                        string curName=curObj->getName();
                        delete curObj;

                        if(curType=="block" && curName=="block")
                        {
                            curObj=new Block();
                            curObj->setName("noHookBlock");
                        }
                        else if(curType=="block" && curName=="noHookBlock")
                        {
                            curObj=new Lava();
                            curObj->setName("Lava");
                        }
                        else if(curType=="lava" && curName=="Lava")
                        {
                            curObj=new Block();
                            curObj->setName("jumpBlock");
                        }
                        else if(curType=="block" && curName=="jumpBlock")
                        {
                            curObj=new Flux();
                            curObj->setName("flux");
                        }
                        else if(curType=="flux" && curName=="flux")
                        {
                            curObj=new BossButan();
                            curObj->setName("bossbutan");
                        }
                        else if(curType=="boss" && curName=="bossbutan")
                        {
                            curObj=new Bonus();
                            curObj->setName("rez");
                        }
                        else if(curType=="bonus" && curName=="rez")
                        {
                            curObj=new Bonus();
                            curObj->setName("health");
                        }
                        else if(curType=="bonus" && curName=="health")
                        {
                            curObj=new Bonus();
                            curObj->setName("rope");
                        }
                        else if(curType=="bonus" && curName=="rope")
                        {
                            curObj=new Bonus();
                            curObj->setName("nextphase");
                        }
                        else if(curType=="bonus" && curName=="nextphase")
                        {
                            curObj=new Bonus();
                            curObj->setName("startboss");
                        }
                        else
                            curObj=new Block();
                        curObj->ini();
                        curObj->setPos(posCur);
                        curObj->setSize(Vector3D(1,1,1));

                        m_camera.setCible(curObj);
                    }
                    break;
                    case SDLK_LSHIFT:
                    if(1)//if I dont do that, compiler gives error... WTF?
                    {
                        //delete colliding objects
                        std::vector<Object*>* os=Map::getInstance()->getObjects();

                        for(unsigned int i=0;i<os->size();i++)
                        {
                            if((*os)[i]->getSize().Z<1000 && curObj->collision((*os)[i]))
                            {
                                delete (*os)[i];
                                os->erase(os->begin()+i);
                            }
                        }
                    }
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
                    case SDLK_b:
                        Map::getInstance()->editor_highestZ=curObj->getPos().Z;
                    break;
                    case SDLK_n:
                        Map::getInstance()->editor_nextZ=curObj->getPos().Z;
                    break;
                    case SDLK_v:
                        Map::getInstance()->killWalls();
                    break;
                    case SDLK_x:
                        Map::getInstance()->setStartPos(curObj->getPos());
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
                    default:
                    break;
                }
                break;
            }
        }

        //update stuff
        updateTimes();
        handleTracer();

        interaction.update();

        Gsounds::getInstance()->update(m_camera.getPos().toLeft(),Vector3D(0,0,0),m_camera.getDir().toLeft(),Vector3D(0,0,1));

        m_video->update(ft);

        draw();

        SDL_Delay(10);


        if(fadingToLeave)
        {
            if(Video::getInstance()->getFade()->getFading()==false)
            {
                Video::getInstance()->getFade()->startFadeIn();
            }
            if(Video::getInstance()->getFade()->getAlpha()>=1)
            {
                playLoop=false;
                fadingToLeave=false;
            }
        }
    }


    close();
}

void Editor::draw(bool toPick)
{
    //draw
    m_video->beforeDraw();

    m_camera.look();

    if(!toPick)
    {
        Lighting::getInstance()->shineAmbiant();
        Lighting::getInstance()->shineAll();
        //origin
        glDisable(GL_TEXTURE_2D);
        glColor4b(255,0,0,255);
        glTranslated(0,0,0);
        glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(1,0,0);
        glVertex3d(0,0,0);
        glVertex3d(0,1,0);
        glVertex3d(0,0,0);
        glVertex3d(0,0,1);
        glEnd();
        glTranslated(0,0,0);
        glEnable(GL_TEXTURE_2D);

    }

    Map::getInstance()->draw();

    if(!toPick)
    {
        if(showCur)
            curObj->draw();

        //m_interface.draw();
        m_chat.draw();

        //fading
        m_video->matrixOrtho2D();
        m_video->getFade()->draw();
        m_video->matrixProjection();
    }

    m_video->afterDraw();

}

void Editor::processHits(GLint hits, GLuint buffer[])
{
    GLuint  names;
    GLuint  *ptr;

    std::cout << "hits = " << hits << std::endl;
    ptr = (GLuint *)buffer;
    for (int i = 0; i < hits; i++)
    {
        //cerr << buffer[i*4] << endl;
        names = *ptr;
        std::cout << " number of names for this hit = " << names << std::endl;
        ptr++;
        std::cout << "  z1 is " << (float) *ptr / 0x7ffffff;
        ptr++;
        std::cout << " z2 is " << (float) *ptr / 0x7ffffff << std::endl;
        ptr++;
        std::cout << "   NAMES ";
        for (unsigned int j = 0; j < names; j++)
        {
            std::cout << *ptr << std::endl;
            int number=*ptr;
            printf("number:%d.",number);
            ptr++;
        }
        std::cout << std::endl;
    }
    std::cout << "\n-----------------------------------------\n" << std::endl;

}
void Editor::pick(double x, double y)
{
    bool pickFace=false;

    draw(true);
    objSelected=0;
    double mouse_x=x;
    double mouse_y=y;
    /*mouse_x=640/2;
    mouse_y=480/2;*/
	GLuint	buffer[2048];// Set Up A Selection Buffer
	GLint	hits;// The Number Of Objects That We Selected

	// The Size Of The Viewport. [0] Is <x>, [1] Is <y>, [2] Is <length>, [3] Is <width>
	GLint	viewport[4];

	// This Sets The Array <viewport> To The Size And Location Of The Screen Relative To The Window
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(2048, buffer);// Tell OpenGL To Use Our Array For Selection

	// Puts OpenGL In Selection Mode. Nothing Will Be Drawn.  Object ID's and Extents Are Stored In The Buffer.
	glRenderMode(GL_SELECT);
    glInitNames();// Initializes The Name Stac
	glPushName(0);// Push 0 (At Least One Entry) Onto The Stack
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is.
	gluPickMatrix((GLdouble) mouse_x, (GLdouble) (viewport[3]-mouse_y), 1.0f, 1.0f, viewport);

	// Apply The Perspective Matrix
	gluPerspective(70, (GLfloat) (viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]), 0.01, 1000);
	glMatrixMode(GL_MODELVIEW);

	if(pickFace==false)
	{
        for(unsigned int i=0;i<(*m_objects).size();i++)
        {
            glLoadName(i);
            (*m_objects)[i]->draw();
        }
        glEnd();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        hits=glRenderMode(GL_RENDER);// Switch To Render Mode, Find Out How Many
        // Objects Were Drawn Where The Mouse Was
        int	choose = buffer[3];// Make Our Selection The First Object
        int depth = buffer[1];// Store How Far Away It Is
        if (hits > 0)// If There Were More Than 0 Hits
        {
            processHits(hits,buffer);

            for (int loop = 1; loop < hits; loop++)// Loop Through All The Detected Hits
            {
                // If This Object Is Closer To Us Than The One We Have Selected
                if (buffer[loop*4+1] < GLuint(depth))
                {
                    choose = buffer[loop*4+3];// Select The Closer Object
                    depth = buffer[loop*4+1];// Store How Far Away It Is
                }
            }
            objSelected=choose;
        }
        else  objSelected=-1;
        if(objSelected<0 || objSelected>=(int)(*m_objects).size())
            objSelected=-1;
        menuObj();
	}
	else
	{
	    int indexpicked=-1;
	    int index=0;//0 1 2 3 4 5// 6 7 8 9 10 11//
        for(unsigned int i=0;i<(*m_objects).size();i++)
        {
            if((*m_objects)[i]->getType()=="block")
            {
                glLoadName(index);
                glPushMatrix();
                glTranslated((*m_objects)[i]->getPos().X,(*m_objects)[i]->getPos().Y,(*m_objects)[i]->getPos().Z+(*m_objects)[i]->getSize().Z);
                glRotated((*m_objects)[i]->getRot().X,1,0,0);
                glRotated((*m_objects)[i]->getRot().Y,0,1,0);
                glRotated((*m_objects)[i]->getRot().Z,0,0,1);
                glBegin(GL_QUADS);
                (*m_objects)[i]->action(100);
                glEnd();
                index++;
                glLoadName(index);
                glBegin(GL_QUADS);
                (*m_objects)[i]->action(101);
                glEnd();
                index++;
                glLoadName(index);
                glBegin(GL_QUADS);
                (*m_objects)[i]->action(102);
                glEnd();
                index++;
                glLoadName(index);
                glBegin(GL_QUADS);
                (*m_objects)[i]->action(103);
                glEnd();
                index++;
                glLoadName(index);
                glBegin(GL_QUADS);
                (*m_objects)[i]->action(104);
                glEnd();
                index++;
                glLoadName(index);
                glBegin(GL_QUADS);
                (*m_objects)[i]->action(105);
                glEnd();
                index++;
                glPopMatrix();
            }
            else
                index+=6;

        }
        glEnd();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        hits=glRenderMode(GL_RENDER);// Switch To Render Mode, Find Out How Many
        // Objects Were Drawn Where The Mouse Was
        int	choose = buffer[3];// Make Our Selection The First Object
        int depth = buffer[1];// Store How Far Away It Is
        if (hits > 0)// If There Were More Than 0 Hits
        {
            processHits(hits,buffer);

            for (int loop = 1; loop < hits; loop++)// Loop Through All The Detected Hits
            {
                // If This Object Is Closer To Us Than The One We Have Selected
                if (buffer[loop*4+1] < GLuint(depth))
                {
                    choose = buffer[loop*4+3];// Select The Closer Object
                    depth = buffer[loop*4+1];// Store How Far Away It Is
                }
            }
            indexpicked=choose;
        }
        else  indexpicked=-1;
        /*cerr<<"indexpicked: "<<indexpicked;
        if(indexpicked!=-1)
        {
            int idObj=floor(indexpicked/6);
            (*m_objects)[idObj]->specific(NULL,40+indexpicked-idObj*6);
            cerr<<"picked face from "<< (*m_objects)[idObj]->getType()<<", id: "<<(*m_objects)[idObj]->getId()<<endl;
        }*/
	}
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
    Vector3D dir=m_camera.getDir().to2D().normalize();
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

    Map::getInstance()->erase();
    Gsounds::getInstance()->freeAll();

    cerr<<"Exited cleanly.";
}


Editor::~Editor()
{

}




