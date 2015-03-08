#ifndef MENUEDITOR_H_INCLUDED
#define MENUEDITOR_H_INCLUDED
#include "Object2D.h"
#include <vector>

void menuEditor(vector<Object2D>* b,freetype::font_data* font)
{
    b->clear();

    unsigned int ind=b->size();
    b->push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/title_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.6,0));
    (*b)[ind].setSize(Vector3D(0.5,0.4,0));
    (*b)[ind].setName("title");

    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/linkocraftcom_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/linkocraftcom_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.04,0.04,0));
    (*b)[ind].setSize(Vector3D(0.3,0.03,0));
    (*b)[ind].setName("linkocraftcom");
    (*b)[ind].setClicable(true);

    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/new_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/new_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.76,0.14,0));
    (*b)[ind].setSize(Vector3D(0.2,0.075,0));
    (*b)[ind].setName("new");
    (*b)[ind].setClicable(true);

    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/delete_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/delete_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.76,0.24,0));
    (*b)[ind].setSize(Vector3D(0.2,0.075,0));
    (*b)[ind].setName("delete");
    (*b)[ind].setClicable(true);

    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/test_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/test_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.76,0.34,0));
    (*b)[ind].setSize(Vector3D(0.2,0.075,0));
    (*b)[ind].setName("test");
    (*b)[ind].setClicable(true);

    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/open_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/open_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.76,0.44,0));
    (*b)[ind].setSize(Vector3D(0.2,0.075,0));
    (*b)[ind].setName("open");
    (*b)[ind].setClicable(true);



    ind=(*b).size();
    (*b).push_back(Object2D());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/back_hq.png"));
    (*b)[ind].setTextureHover(GTexture::getInstance()->getTexture("../data/textures/interface/back_hover_hq.png"));
    (*b)[ind].setPos(Vector3D(0.76,0.04,0));
    (*b)[ind].setSize(Vector3D(0.2,0.075,0));
    (*b)[ind].setName("back");
    (*b)[ind].setClicable(true);


    vector<string> maps;
    vector<string> folders;
    maps.clear();
    folders.clear();

    DIR *dir;
    struct dirent *lecture;
    std::string en_cours="";

    string chardir="";
    /*if(savetxt!="")
        chardir=savetxt;
    else*/
        chardir="../data/patterns/";

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
        else if(strstr(lecture->d_name,".")==NULL)
        {
            en_cours=chardir;
            en_cours+=lecture->d_name;
            folders.push_back(en_cours);
        }
    }



    for(unsigned int i=0;i<maps.size();i++)
    {

        ind=(*b).size();
        (*b).push_back(Object2D());
        (*b)[ind].setPos(Vector3D(0.1,0.5-(i+folders.size())/20.0,0));
        (*b)[ind].setSize(Vector3D(0.5,0.05,0));
        (*b)[ind].addText(maps[i],font);
        (*b)[ind].setName(maps[i]);
        (*b)[ind].setClicable(true);

        /*boutons.push_back(Bouton());
        ind=boutons.size()-1;
        boutons[ind].texte=maps[i].substr(0,maps[i].size()-4);
        boutons[ind].m_x=0.1;
        boutons[ind].m_y=0.7-(i+folders.size())/20.0;
        boutons[ind].ini(aldisplay->largeur,aldisplay->hauteur,&m_font);*/
    }
}



#endif // MENUEDITOR_H_INCLUDED
