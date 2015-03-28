#include "Game.h"




void Game::endLevel()
{
    if(!Online::getInstance()->active() && !levelEnded)
    {
        levelEnded=true;
        SDL_ShowCursor(SDL_ENABLE);//cursor
        SDL_WM_GrabInput(SDL_GRAB_OFF);

        vector<Button> buttons;
        buttons.clear();

        //time
        unsigned ind=buttons.size();
        buttons.push_back(Button());
        buttons[ind].setPos(Vector3D(0.25,0.6,0));
        buttons[ind].setSize(Vector3D(0.5,0.075,0));
        buttons[ind].setName("Well done!");
        buttons[ind].addText("Well done!");
        buttons[ind].ini();
        buttons[ind].setTexture(NULL);
        buttons[ind].setClicable(false);
        //time
        /*ind=buttons.size();
        buttons.push_back(Button());
        buttons[ind].setPos(Vector3D(0.25,0.65,0));
        buttons[ind].setSize(Vector3D(0.5,0.075,0));
        buttons[ind].setName("time");
        stringstream ss;
        ss<<"Time: "<<0;
        buttons[ind].addText(ss.str());
        buttons[ind].ini();
        buttons[ind].setTexture(NULL);
        buttons[ind].setClicable(false);
        //score
        ind=buttons.size();
        buttons.push_back(Button());
        buttons[ind].setPos(Vector3D(0.25,0.6,0));
        buttons[ind].setSize(Vector3D(0.5,0.075,0));
        buttons[ind].setName("score");
        stringstream ss2;
        ss2<<"Score: "<<0;
        buttons[ind].addText(ss2.str());
        buttons[ind].ini();
        buttons[ind].setTexture(NULL);
        buttons[ind].setClicable(false);
        //send score online
        ind=buttons.size();
        buttons.push_back(Button());
        buttons[ind].setPos(Vector3D(0.25,0.5,0));
        buttons[ind].setSize(Vector3D(0.5,0.075,0));
        buttons[ind].setName("Send Score Online");
        buttons[ind].addText("Send Score Online");
        buttons[ind].ini();*/
        //next level
        ind=buttons.size();
        buttons.push_back(Button());
        buttons[ind].setPos(Vector3D(0.25,0.45,0));
        buttons[ind].setSize(Vector3D(0.5,0.075,0));
        buttons[ind].setName("Next Level");
        buttons[ind].addText("Next Level");
        buttons[ind].ini();
        //restart
        ind=buttons.size();
        buttons.push_back(Button());
        buttons[ind].setPos(Vector3D(0.25,0.35,0));
        buttons[ind].setSize(Vector3D(0.5,0.075,0));
        buttons[ind].setName("Restart");
        buttons[ind].addText("Restart");
        buttons[ind].ini();
        //quit
        ind=buttons.size();
        buttons.push_back(Button());
        buttons[ind].setPos(Vector3D(0.25,0.25,0));
        buttons[ind].setSize(Vector3D(0.5,0.075,0));
        buttons[ind].setName("Quit");
        buttons[ind].addText("Quit");
        buttons[ind].ini();

        bool menuLoop=true;


        while (menuLoop)
        {
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_QUIT:
                        playLoop=false;
                        menuLoop=false;
                    break;

                    case SDL_MOUSEMOTION:
                        for(unsigned int i=0;i<buttons.size();i++)
                            buttons[i].updateCursor(Vector3D(event.button.x,event.button.y,0));
                    break;

                    case SDL_MOUSEBUTTONUP:
                    if(event.button.button==SDL_BUTTON_LEFT)
                    {
                        for(unsigned int i=0;i<buttons.size();i++)
                        {
                            if(buttons[i].getClicable() && buttons[i].clic(Vector3D(event.button.x,event.button.y,0)))
                            {
                                Gsounds::getInstance()->play("../data/sounds/hover.mp3");
                                if(buttons[i].getName().find("Send Score Online")!=string::npos)
                                {
                                    char url[255]="www.linkocraft.com";
                                    ShellExecute(NULL, "open", url,NULL, NULL, SW_SHOWNORMAL);
                                }
                                else if(buttons[i].getName().find("Next Level")!=string::npos)
                                {
                                    menuLoop=false;
                                    fadingToLeave=true;

                                    //find which level is next
                                    string nextLvl="";

                                    vector<string> maps;
                                    maps.clear();

                                    DIR *dir;
                                    struct dirent *lecture;
                                    std::string en_cours="";

                                    string chardir="../data/levels/";

                                    char* tempchemin=stringtochar(chardir);
                                    dir = opendir(tempchemin);
                                    delete tempchemin;
                                    tempchemin=NULL;

                                    while ((lecture = readdir(dir)))
                                    {
                                        if(strstr(lecture->d_name,".txt")!=NULL)
                                        {
                                            en_cours=chardir;
                                            en_cours+=lecture->d_name;
                                            maps.push_back(en_cours);
                                        }
                                    }

                                    for(unsigned int i=0;i<maps.size();i++)
                                    {
                                        cerr <<"map: "<< maps[i]<<endl;
                                        cerr <<"pathTest: "<< pathTest<<endl;
                                        if(pathTest==maps[i])
                                        {
                                            if(i<maps.size()+1)
                                                nextLvl=maps[i+1];
                                            break;
                                        }
                                    }
                                    //if there is a next level, play it. otherwise go to menu
                                    if(nextLvl!="")
                                        command="play "+nextLvl;
                                    else
                                        command="menu";
                                }
                                else if(buttons[i].getName().find("Restart")!=string::npos)
                                {
                                    menuLoop=false;
                                    fadingToLeave=true;
                                }
                                else if(buttons[i].getName().find("Quit")!=string::npos)
                                {
                                    fadingToLeave=true;
                                    menuLoop=false;
                                    command="menu";
                                }
                                break;
                            }
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
                        case SDLK_SPACE:
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
                        break;
                        case SDLK_ESCAPE:
                        playLoop=false;
                        menuLoop=false;
                        break;
                        default:
                        break;
                    }
                    break;
                }
            }

            //update stuff
            updateTimes();
            //m_online->update();

            m_video->update(ft);

            for(unsigned int i=0;i<buttons.size();i++)
                buttons[i].update(ft);


            draw();
            for(unsigned int i=0;i<buttons.size();i++)
                buttons[i].draw();

            m_video->afterDraw();

            SDL_Delay(20);

        }
    }
}
