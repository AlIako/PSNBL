#ifndef MENUSINGLE_H_INCLUDED
#define MENUSINGLE_H_INCLUDED
#include "Object2D.h"
#include <vector>

void menuSingle(vector<Button>* b)
{
    b->clear();

    unsigned int ind=b->size();
    b->push_back(Button());
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/title_hq.png"));
    (*b)[ind].setPos(Vector3D(0.25,0.6,0));
    (*b)[ind].setSize(Vector3D(0.5,0.4,0));
    (*b)[ind].setName("title");

    ind=(*b).size();
    b->push_back(Button());
    (*b)[ind].setPos(Vector3D(0.04,0.04,0));
    (*b)[ind].setSize(Vector3D(0.3,0.03,0));
    (*b)[ind].setName("linkocraftcom");
    (*b)[ind].addText("www.linkocraft.com");
    (*b)[ind].ini();
    (*b)[ind].centerText(false);
    (*b)[ind].setTexture(NULL);

    ind=(*b).size();
    b->push_back(Button());
    (*b)[ind].setPos(Vector3D(0.76,0.04,0));
    (*b)[ind].setSize(Vector3D(0.2,0.075,0));
    (*b)[ind].setName("back");
    (*b)[ind].addText("Back");
    (*b)[ind].ini();
    (*b)[ind].setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_small.png"));


    vector<string> maps;
    vector<string> folders;
    maps.clear();
    folders.clear();

    DIR *dir;
    struct dirent *lecture;
    std::string en_cours="";

    string chardir="";

        chardir="../data/levels/";

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
        (*b).push_back(Button());
        (*b)[ind].setPos(Vector3D(0.1,0.5-(i+folders.size())/20.0,0));
        (*b)[ind].setSize(Vector3D(0.5,0.05,0));
        (*b)[ind].addText(maps[i]);
        (*b)[ind].setName(maps[i]);
        (*b)[ind].ini();
        (*b)[ind].setSelectable(true);
        (*b)[ind].centerText(false);
        (*b)[ind].setTexture(NULL);
    }
}



#endif // MENUSINGLE_H_INCLUDED
