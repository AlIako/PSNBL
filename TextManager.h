#ifndef TEXTMANAGER_H_INCLUDED
#define TEXTMANAGER_H_INCLUDED
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Video.h"
#include "Gtexture.h"

//old freetype library
#include "freetype.h"

using namespace std;

class TextManager
{
public:
    static TextManager* getInstance();

    void ini();


    void render_text(const char *text, float x, float y, float sx, float sy);
    void display();

    void displayText(string t);


    freetype::font_data* getFont() {return &m_font;}


private:
    TextManager();
    static TextManager* m_instance;

    //old lib
    freetype::font_data m_font;

    //new lib
    GLuint tex;
    GLint uniform_tex;

    FT_Library ft;
    FT_Face face;
    FT_GlyphSlot g;

};


#endif // TEXTMANAGER_H_INCLUDED
