#ifndef TEXTMANAGER_H_INCLUDED
#define TEXTMANAGER_H_INCLUDED
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Video.h"
#include "Gtexture.h"
#include "freetype.h"

using namespace std;

class TextManager
{
public:
    static TextManager* getInstance();

    void ini();
    freetype::font_data* getFont() {return &m_font;}


private:
    TextManager();
    static TextManager* m_instance;

    //old lib
    freetype::font_data m_font;

};


#endif // TEXTMANAGER_H_INCLUDED
