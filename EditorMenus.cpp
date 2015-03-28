#include "Editor.h"




void Editor::iniInterf()
{
    interf_editor.clear();
    int ind=0;
    interf_editor.push_back(Button());
    ind=interf_editor.size()-1;
    interf_editor[ind].addText("Texture");
    interf_editor[ind].setName("Texture");
    interf_editor[ind].setPos(Vector3D(0.1,0.9,0));
    interf_editor[ind].ini();
    interf_editor[ind].setTexture(NULL);
    interf_editor[ind].centerText(false);

    interf_editor.push_back(Button());
    ind=interf_editor.size()-1;
    interf_editor[ind].addText(curObj->getType());
    interf_editor[ind].setName(curObj->getType());
    interf_editor[ind].setPos(Vector3D(0.1,0.8,0));
    //interf_editor[ind].m_texture=gtext->getTexture("data/textures/objs/"+lilian->getType()+".png");
    interf_editor[ind].ini();
    interf_editor[ind].setTexture(NULL);
    interf_editor[ind].centerText(false);

    interf_editor.push_back(Button());
    ind=interf_editor.size()-1;
    interf_editor[ind].addText("Quit");
    interf_editor[ind].setName("Quit");
    interf_editor[ind].setPos(Vector3D(0.05,0.05,0));
    interf_editor[ind].ini();
    interf_editor[ind].setTexture(NULL);
    interf_editor[ind].centerText(false);

    interf_editor.push_back(Button());
    ind=interf_editor.size()-1;
    interf_editor[ind].addText("Save");
    interf_editor[ind].setName("Save");
    interf_editor[ind].setPos(Vector3D(0.05,0.1,0));
    interf_editor[ind].ini();
    interf_editor[ind].setTexture(NULL);
    interf_editor[ind].centerText(false);

}


void Editor::menuObj()
{
    //unselect all; select concerned obj.
    for(unsigned int i=0;i<m_objects->size();i++)
    {
        if((int)i==objSelected)
            (*m_objects)[i]->select(true);
        else
            (*m_objects)[i]->select(false);
    }

    stringstream ss;
    ss<<"picking object id: "<<objSelected;
    Tracer::getInstance()->trace("editor",ss.str());

    if(objSelected>=0)
    {
        (*m_objects)[objSelected]->setButtons(&buttons);
        for(unsigned int i=0;i<buttons.size();i++)
        {
            buttons[i].ini();
            buttons[i].setTexture(NULL);
        }

        int tempsPrecedent=SDL_GetTicks(), tempsActuel=tempsPrecedent;
        SDL_Event event;
        bool continuer=true;
        while (continuer)
        {
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_QUIT:
                    continuer=false;
                    playLoop=false;
                    command="quit";
                    break;
                    case SDL_MOUSEMOTION:
                    for(unsigned int i=0;i<buttons.size();i++)
                        buttons[i].updateCursor(Vector3D(event.button.x,event.button.y,0));
                    break;
                    case SDL_MOUSEBUTTONUP:
                    if(event.button.button==SDL_BUTTON_WHEELUP)
                        for(unsigned int i=0;i<buttons.size();i++)
                            buttons[i].translate(0,-0.05);
                    else if(event.button.button==SDL_BUTTON_WHEELDOWN)
                        for(unsigned int i=0;i<buttons.size();i++)
                            buttons[i].translate(0,0.05);
                    else if(event.button.button==SDL_BUTTON_LEFT)
                    {
                        for(unsigned int i=0;i<buttons.size();i++)
                            if(buttons[i].clic(Vector3D(event.button.x,event.button.y,0)))
                            {
                                (*m_objects)[objSelected]->checkClicks(&buttons,i);
                                if(buttons[i].needwhat=="int")
                                {
                                    buttons[i].applyChangesVariable(entrerNombre(*buttons[i].int_change));
                                }
                                else if(buttons[i].needwhat=="double")
                                {
                                    buttons[i].applyChangesVariable((double)entrerNombre((int)*buttons[i].dou_change*10)/10);
                                }
                                else if(buttons[i].needwhat=="string" && (*m_objects)[objSelected]->getType()!="bonus")
                                {
                                    buttons[i].applyChangesVariable(entrerString(buttons[i].str_change));
                                }
                                else if(buttons[i].needwhat=="vector")
                                {
                                    buttons[i].applyChangesVariable(modifVector(buttons[i].vec_change,buttons[i].getTxt(),0.5));
                                }
                                else if(buttons[i].getTxt().find("texture: ")!=string::npos)
                                {
                                    string text_cur=choseFile("une texture","../data/textures",true,".jpg",".JPG",".png");
                                    if(text_cur!="../data/textures")
                                    {
                                        (*m_objects)[objSelected]->setTexture(GTexture::getInstance()->addGetTexture(text_cur));
                                        if((*m_objects)[objSelected]->getTexture())
                                        {
                                            buttons[i].addAuTexte((*m_objects)[objSelected]->getTexture()->getChemin());
                                            buttons[i].ini();
                                            buttons[i].setTexture(NULL);
                                            buttons[i].centerText(false);
                                        }
                                    }
                                }
                                /*else if(buttons[i].getTxt().find("mesh: ")!=string::npos)
                                {
                                    string text_cur=choseFile("un mesh","data/models",true,".obj");
                                    if(text_cur!="../data/models")
                                    {
                                        models->addMesh(text_cur);
                                        (*m_objects)[objSelected]->setMesh(models->getMesh(text_cur),1);
                                    }
                                    buttons[i].addAuTexte((*m_objects)[objSelected]->getMesh()->getRepertoire());
                                    buttons[i].ini(aldisplay->largeur,aldisplay->hauteur);
                                }*/
                                else if(buttons[i].getTxt().find("son: ")!=string::npos)
                                {
                                    string text_cur=choseFile("un son","../data/sounds",true,".wav",".WAV",".mp3");
                                    /*if(text_cur!="../data/sounds")
                                        (*m_objects)[objSelected]->specific(text_cur,1);*/
                                    buttons[i].addAuTexte(text_cur);
                                    buttons[i].ini();
                                    buttons[i].setTexture(NULL);
                                    buttons[i].centerText(false);
                                }
                                else if(buttons[i].getTxt()=="OK")
                                {
                                    continuer=false;
                                }
                                for(unsigned int i=0;i<buttons.size();i++)
                                {
                                    buttons[i].ini();
                                    buttons[i].setTexture(NULL);
                                    buttons[i].centerText(false);
                                }
                            }
                    }
                    else if(event.button.button==SDL_BUTTON_RIGHT)
                        continuer=false;
                    break;
                    case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                        for(unsigned int i=0;i<buttons.size();i++)
                            buttons[i].translate(0,-0.05);
                        break;
                        case SDLK_DOWN:
                        for(unsigned int i=0;i<buttons.size();i++)
                            buttons[i].translate(0,0.05);
                        break;
                        default:
                        break;
                    }
                    break;
                    case SDL_KEYUP:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        continuer=false;
                        break;
                        case SDLK_DELETE:
                        delete (*m_objects)[objSelected];
                        (*m_objects)[objSelected]=NULL;
                        for(unsigned int j=objSelected;j<(*m_objects).size()-1;j++)
                        {
                            (*m_objects)[j]=(*m_objects)[j+1];
                        }
                        (*m_objects).pop_back();
                        continuer=false;
                        break;
                        case SDLK_c:
                        curObj->setTexture((*m_objects)[objSelected]->getTexture());
                        curObj->setType((*m_objects)[objSelected]->getType());
                        curObj->setPhysical((*m_objects)[objSelected]->getPhysical());
                        //curObj->setDessin((*m_objects)[objSelected]->getDessin());
                        //curObj->setMov((*m_objects)[objSelected]->getMov());
                        curObj->setSize((*m_objects)[objSelected]->getSize());
                        //if((*m_objects)[objSelected]->getMesh()!=NULL)
                        //    curObj->setMesh((*m_objects)[objSelected]->getMesh(),(*m_objects)[objSelected]->getScaleMesh());
                        continuer=false;
                        break;
                        default:
                        break;
                    }
                    break;
                    default:
                    break;
                }
            }
            for(unsigned int i=0;i<buttons.size();i++)
                if(buttons[i].clic(Vector3D(event.button.x,event.button.y,0)))
                    buttons[i].select(true);
                else buttons[i].select(false);

            draw();
            for(unsigned int i=0;i<buttons.size();i++)
                buttons[i].draw();

            Video::getInstance()->afterDraw();

            //temps, FPSmax=60
            tempsActuel = SDL_GetTicks();
            if (tempsActuel - tempsPrecedent > 30)
                tempsPrecedent = tempsActuel;
            else
                SDL_Delay(30 - (tempsActuel - tempsPrecedent));

            }
    }

    buttons.clear();
    objSelected=-1;
}




string Editor::choseFile(string what,string c, bool fullname, string type1, string type2, string type3)
{
    string erg=c;

    vector<Button> bout;
    bout.clear();
    int ind=0;
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("Choisir "+what+": ");
    bout[ind].setName("Choisir");
    bout[ind].setPos(Vector3D(-0.5,0.9,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);

    vector<string> texts;
    texts.clear();
    DIR *dir;
    struct dirent *lecture;
    std::string en_cours="";

    char* tempchemin=stringtochar(c);
    dir = opendir(tempchemin);
    delete tempchemin;
    tempchemin=NULL;

    while ((lecture = readdir(dir)))
    {
        if((strstr(lecture->d_name,stringtochar(type1))!=NULL && type1!="") ||
           (strstr(lecture->d_name,stringtochar(type2))!=NULL && type2!="") ||
            (strstr(lecture->d_name,stringtochar(type3))!=NULL && type3!=""))
        {
            en_cours=c+"/";
            en_cours+=lecture->d_name;
            texts.push_back(en_cours);
        }
    }
    for(unsigned int i=0;i<texts.size();i++)
    {
        bout.push_back(Button());
        ind=bout.size()-1;
        string gjbi=texts[i];
        if(!fullname)
        {
            gjbi=gjbi.substr(0,gjbi.size()-4);
            gjbi=gjbi.substr(c.size()+1,gjbi.size());
        }
        bout[ind].addText(gjbi);
        bout[ind].setName(gjbi);
        GTexture::getInstance()->addTexture(texts[i]);
        bout[ind].setTexture(GTexture::getInstance()->getTexture(texts[i]));
        bout[ind].setPos(Vector3D(0.2,0.8-i/15.0,0));
        bout[ind].ini();
        bout[ind].setTexture(NULL);
        bout[ind].centerText(false);
        //bout[ind].colImage=true;

        //preview
        bout.push_back(Button());
        ind=bout.size()-1;
        bout[ind].setName(gjbi);
        GTexture::getInstance()->addTexture(texts[i]);
        bout[ind].setPos(Vector3D(0.1,0.8-i/15.0,0));
        bout[ind].setSize(Vector3D(0.05,0.05,0));
        bout[ind].ini();
        bout[ind].setTexture(GTexture::getInstance()->getTexture(texts[i]));
    }
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("Retour");
    bout[ind].setName("Retour");
    bout[ind].setPos(Vector3D(-0.5,0.8-texts.size()/15.0,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);

    if(what=="une texture")
        for(unsigned int i=0;i<bout.size();i++)
            bout[i].translate(0,yboutonstexture);



    int tempsPrecedent=SDL_GetTicks(), tempsActuel=tempsPrecedent;
    SDL_Event event;
    bool continuer=true;
    while (continuer)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                playLoop=false;
                continuer=false;
                command="quit";
                break;
                case SDL_MOUSEMOTION:
                for(unsigned int i=0;i<bout.size();i++)
                    bout[i].updateCursor(Vector3D(event.button.x,event.button.y,0));
                break;
                case SDL_MOUSEBUTTONUP:
                if(event.button.button==SDL_BUTTON_WHEELUP)
                {
                    if(what=="une texture")
                        yboutonstexture-=0.1;
                    for(unsigned int i=0;i<bout.size();i++)
                        bout[i].translate(0,-0.1);
                }
                else if(event.button.button==SDL_BUTTON_WHEELDOWN)
                {
                    if(what=="une texture")
                        yboutonstexture+=0.1;
                    for(unsigned int i=0;i<bout.size();i++)
                        bout[i].translate(0,0.1);
                }
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    for(unsigned int i=0;i<bout.size();i++)
                        if(bout[i].clic(Vector3D(event.button.x,event.button.y,0)))
                        {
                            if(bout[i].getName().find("Retour")==string::npos && bout[i].getName().find("Choisir une texture: ")==string::npos)
                                return bout[i].getName();
                            else if(bout[i].getName().find("Retour")!=string::npos) return c;

                        }
                }
                break;
                case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    continuer=false;
                    break;
                    default:
                    break;
                }
                break;
                case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                    for(unsigned int i=0;i<bout.size();i++)
                        bout[i].translate(0,-0.05);
                    break;
                    case SDLK_DOWN:
                    for(unsigned int i=0;i<bout.size();i++)
                        bout[i].translate(0,0.05);
                    break;
                    default:
                    break;
                }
                break;
                default:
                break;
            }
        }
        for(unsigned int i=0;i<bout.size();i++)
            if(bout[i].clic(Vector3D(event.button.x,event.button.y,0)) && bout[i].getTxt()!="Choisir une texture: ")
                bout[i].select(true);
            else bout[i].select(false);

        draw();
        /*for(unsigned int i=0;i<boutons.size();i++)
            boutons[i].display();*/
        for(unsigned int i=0;i<bout.size();i++)
            bout[i].draw();
        glFlush();
        SDL_GL_SwapBuffers();

        //temps, FPSmax=60
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 30)
            tempsPrecedent = tempsActuel;
        else
            SDL_Delay(30 - (tempsActuel - tempsPrecedent));

    }
    return c;
}
void delDigit(int* a)
{
    *a/=10;
}
void addDigit(int* a, int d)
{
    *a*=10;
    *a+=d;
}
int Editor::entrerNombre(int erg)
{
    int cur_nombre=erg;
    vector<Button> bout;
    bout.clear();
    int ind=0;
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].setText("Entrer un nombre: ");
    bout[ind].setPos(Vector3D(-0.5,0.7,0));
    bout[ind].ini();
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].setText("Ok");
    bout[ind].setPos(Vector3D(0.45,0.6,0));
    bout[ind].ini();
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].setText("Annuler");
    bout[ind].setPos(Vector3D(0.5,0.6,0));
    bout[ind].ini();
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].setText("");
    bout[ind].addAuTexte(cur_nombre);
    bout[ind].setPos(Vector3D(-0.5,0.65,0));
    bout[ind].ini();

    int tempsPrecedent=SDL_GetTicks(), tempsActuel=tempsPrecedent;
    SDL_Event event;
    bool continuer=true;
    while (continuer)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                playLoop=false;
                cur_nombre=erg;
                continuer=false;
                command="quit";
                break;
                case SDL_MOUSEMOTION:
                for(unsigned int i=0;i<bout.size();i++)
                    bout[i].updateCursor(Vector3D(event.button.x,event.button.y,0));
                break;
                case SDL_MOUSEBUTTONUP:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    for(unsigned int i=0;i<bout.size();i++)
                        if(bout[i].clic(Vector3D(event.button.x,event.button.y,0)))
                        {
                            if(bout[i].getTxt()=="Annuler")
                            {
                                return erg;
                            }
                            else if(bout[i].getTxt()=="Ok")
                            {
                                erg=cur_nombre;
                                return erg;
                            }
                        }
                }
                break;
                case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    default:
                    break;
                }
                break;
                case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    continuer=false;
                    break;
                    case SDLK_KP0:
                    addDigit(&cur_nombre,0);
                    break;
                    case SDLK_KP1:
                    addDigit(&cur_nombre,1);
                    break;
                    case SDLK_KP2:
                    addDigit(&cur_nombre,2);
                    break;
                    case SDLK_KP3:
                    addDigit(&cur_nombre,3);
                    break;
                    case SDLK_KP4:
                    addDigit(&cur_nombre,4);
                    break;
                    case SDLK_KP5:
                    addDigit(&cur_nombre,5);
                    break;
                    case SDLK_KP6:
                    addDigit(&cur_nombre,6);
                    break;
                    case SDLK_KP7:
                    addDigit(&cur_nombre,7);
                    break;
                    case SDLK_KP8:
                    addDigit(&cur_nombre,8);
                    break;
                    case SDLK_KP9:
                    addDigit(&cur_nombre,9);
                    break;
                    case SDLK_BACKSPACE:
                    delDigit(&cur_nombre);
                    break;
                    default:
                    break;
                }
                ind=bout.size()-1;
                bout[ind].setText("");
                bout[ind].addAuTexte(cur_nombre);
                bout[ind].ini();
                break;
                default:
                break;
            }
        }
        for(unsigned int i=0;i<bout.size();i++)
            if(bout[i].clic(Vector3D(event.button.x,event.button.y,0)) && bout[i].getTxt()!="Entrer un nombre: ")
                bout[i].select(true);
            else bout[i].select(false);

        draw();
        /*for(unsigned int i=0;i<boutons.size();i++)
            boutons[i].display();*/
        for(unsigned int i=0;i<bout.size();i++)
            bout[i].draw();
        glFlush();
        SDL_GL_SwapBuffers();

        //temps, FPSmax=60
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 30)
            tempsPrecedent = tempsActuel;
        else
            SDL_Delay(30 - (tempsActuel - tempsPrecedent));

        }
    return erg;
}
string Editor::entrerString(string *s)
{
    /*chat->openNeedString(*s,0.001);
    vector<Button> bout;
    bout.clear();
    int ind=0;
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].texte="Enter a string and press ENTER: ";
    bout[ind].m_x=-0.5;
    bout[ind].m_y=0.6;
    bout[ind].ini(aldisplay->largeur,aldisplay->hauteur,&m_font);

    int tempsPrecedent=SDL_GetTicks(), tempsActuel=tempsPrecedent;
    SDL_Event event;
    while (chat->boxOpened())
    {
        chat->checkKeyboard();
        for(unsigned int i=0;i<bout.size();i++)
            if(bout[i].click(event.button.x,event.button.y) && bout[i].texte!="Enter a string and press ENTER: ")
                bout[i].selec=true;
            else bout[i].selec=false;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glClearColor(0.0f, 0.0f, 0.0f, 0.5);

        camera.iniPos();
        camera.look();
        grille.adjustCam(&camera);
        updateTimes();
        draw();
        for(unsigned int i=0;i<bout.size();i++)
            bout[i].display();
        chat->draw();
        glFlush();
        SDL_GL_SwapBuffers();

        //temps, FPSmax=60
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 30)
            tempsPrecedent = tempsActuel;
        else
            SDL_Delay(30 - (tempsActuel - tempsPrecedent));

        }
    chat->closeTextBox();
    *s=chat->nextMessage.msg;
    return chat->nextMessage.msg;*/

    return "";
}
Vector3D Editor::modifVector(Vector3D v, string nom, double pas)
{
    Vector3D vcur=v;
    return modifVector(&vcur,nom,pas);
}
Vector3D Editor::modifVector(Vector3D *v, string nom, double pas)
{
    Vector3D v_ini=*v;
    vector<Button> bout;
    bout.clear();
    int ind=0;
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("Vecteur "+nom);
    bout[ind].setName("Vector");
    bout[ind].setPos(Vector3D(0.4,0.7,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);

    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("X: ");
    bout[ind].setName("X");
    bout[ind].addAuTexte(v->X);
    bout[ind].setPos(Vector3D(0.4,0.6,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("-");
    bout[ind].setName("-");
    bout[ind].setPos(Vector3D(0.5,0.6,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("+");
    bout[ind].setName("+");
    bout[ind].setPos(Vector3D(0.52,0.6,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);




    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("Y: ");
    bout[ind].setName("Y");
    bout[ind].addAuTexte(v->Y);
    bout[ind].setPos(Vector3D(0.4,0.55,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("-");
    bout[ind].setName("-");
    bout[ind].setPos(Vector3D(0.5,0.55,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("+");
    bout[ind].setName("+");
    bout[ind].setPos(Vector3D(0.52,0.55,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);


    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("Z: ");
    bout[ind].setName("Z");
    bout[ind].addAuTexte(v->Z);
    bout[ind].setPos(Vector3D(0.4,0.5,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("-");
    bout[ind].setName("-");
    bout[ind].setPos(Vector3D(0.5,0.5,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("+");
    bout[ind].setName("+");
    bout[ind].setPos(Vector3D(0.52,0.5,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);


    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("pas: ");
    bout[ind].setName("pas");
    bout[ind].addAuTexte(pas);
    bout[ind].setPos(Vector3D(0.4,0.45,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("-");
    bout[ind].setName("-");
    bout[ind].setPos(Vector3D(0.53,0.45,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("+");
    bout[ind].setName("+");
    bout[ind].setPos(Vector3D(0.55,0.45,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);


    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("Ok");
    bout[ind].setName("Ok");
    bout[ind].setPos(Vector3D(0.45,0.4,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);
    bout.push_back(Button());
    ind=bout.size()-1;
    bout[ind].addText("Annuler");
    bout[ind].setName("Annuler");
    bout[ind].setPos(Vector3D(0.5,0.4,0));
    bout[ind].ini();
    bout[ind].setTexture(NULL);
    bout[ind].centerText(false);

    int tempsPrecedent=SDL_GetTicks(), tempsActuel=tempsPrecedent;
    SDL_Event event;
    bool continuer=true;
    while (continuer)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                playLoop=false;
                //para="quitter";
                *v=v_ini;
                continuer=false;
                command="quit";
                break;
                case SDL_MOUSEMOTION:
                for(unsigned int i=0;i<bout.size();i++)
                    bout[i].updateCursor(Vector3D(event.button.x,event.button.y,0));
                break;
                case SDL_MOUSEBUTTONUP:
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    for(unsigned int i=0;i<bout.size();i++)
                        if(bout[i].clic(Vector3D(event.button.x,event.button.y,0)))
                        {
                            Gsounds::getInstance()->play("../data/sounds/hover.mp3");
                            if(bout[i].getTxt().find("Annuler")!=string::npos)
                            {
                                *v=v_ini;
                                return v_ini;
                            }
                            else if(bout[i].getTxt().find("Ok")!=string::npos)
                                return *v;
                            else if(bout[i].getTxt().find("+")!=string::npos)
                            {
                                if(bout[i].getPos().Y==0.6)
                                {
                                    v->X+=pas;
                                    bout[1].addAuTexte(v->X);
                                    bout[1].ini();
                                    bout[1].setTexture(NULL);
                                }
                                else if(bout[i].getPos().Y==0.55)
                                {
                                    v->Y+=pas;
                                    bout[4].addAuTexte(v->Y);
                                    bout[4].ini();
                                    bout[4].setTexture(NULL);
                                }
                                else if(bout[i].getPos().Y==0.5)
                                {
                                    v->Z+=pas;
                                    bout[7].addAuTexte(v->Z);
                                    bout[7].ini();
                                    bout[7].setTexture(NULL);
                                }
                                else if(bout[i].getPos().Y==0.45)
                                {
                                    pas*=2.0;
                                    bout[10].addAuTexte(pas);
                                    bout[10].ini();
                                    bout[10].setTexture(NULL);
                                }
                            }
                            else if(bout[i].getTxt().find("-")!=string::npos)
                            {
                                if(bout[i].getPos().Y==0.6)
                                {
                                    v->X-=pas;
                                    bout[1].addAuTexte(v->X);
                                    bout[1].ini();
                                    bout[1].setTexture(NULL);
                                }
                                else if(bout[i].getPos().Y==0.55)
                                {
                                    v->Y-=pas;
                                    bout[4].addAuTexte(v->Y);
                                    bout[4].ini();
                                    bout[4].setTexture(NULL);
                                }
                                else if(bout[i].getPos().Y==0.5)
                                {
                                    v->Z-=pas;
                                    bout[7].addAuTexte(v->Z);
                                    bout[7].ini();
                                    bout[7].setTexture(NULL);
                                }
                                else if(bout[i].getPos().Y==0.45)
                                {
                                    pas/=2.0;
                                    bout[10].addAuTexte(pas);
                                    bout[10].ini();
                                    bout[10].setTexture(NULL);
                                }
                            }
                        }
                }
                break;
                case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    continuer=false;
                    break;
                    default:
                    break;
                }
                break;
                default:
                break;
            }
        }
        for(unsigned int i=0;i<bout.size();i++)
            if(bout[i].clic(Vector3D(event.button.x,event.button.y,0)) && bout[i].getTxt()!="Entrer un nombre: ")
                bout[i].select(true);
            else bout[i].select(false);

        draw();
        /*for(unsigned int i=0;i<boutons.size();i++)
            boutons[i].display();*/
        for(unsigned int i=0;i<bout.size();i++)
            bout[i].draw();
        glFlush();
        SDL_GL_SwapBuffers();

        //temps, FPSmax=60
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 30)
            tempsPrecedent = tempsActuel;
        else
            SDL_Delay(30 - (tempsActuel - tempsPrecedent));

        }
    *v=v_ini;
    return *v;
}






