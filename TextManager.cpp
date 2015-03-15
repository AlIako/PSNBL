#include "TextManager.h"

TextManager* TextManager::m_instance = new TextManager();


TextManager* TextManager::getInstance()
{
    return m_instance;
}


TextManager::TextManager()
{

}


void TextManager::ini()
{


    //old lib
    m_font.init("../data/fonts/arial.TTF", 16);







    //new lib
    if(FT_Init_FreeType(&ft))
        cerr<<"Could not init freetype library"<<endl;

    if(FT_New_Face(ft, "../data/fonts/arial.ttf", 0, &face))
        cerr<<"Could not open font"<<endl;

    FT_Set_Pixel_Sizes(face, 0, 48);

    //loading character x
    if(FT_Load_Char(face, 'X', FT_LOAD_RENDER))
        cerr<<"Could not load character X"<<endl;

    g=face->glyph;





    //ini texture
    uniform_tex=Video::getInstance()->programIDText;


    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glUniform1i(uniform_tex, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


    int attribute_coord=0;

    GLuint vbo;

    glGenBuffers(1, &vbo);
    glEnableVertexAttribArray(attribute_coord);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
}


void TextManager::displayText(string t)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}




void TextManager::render_text(const char *text, float x, float y, float sx, float sy)
{
  const char *p;

  for(p = text; *p; p++)
    {
    if(FT_Load_Char(face, *p, FT_LOAD_RENDER))
        cerr<<"Error loading char."<<endl;
    //else cerr<<"char "<<p<<" loaded."<<endl;
        //continue;
    g=face->glyph;

    cerr<<"width: "<<g->bitmap.width<<endl;
    cerr<<"rows: "<<g->bitmap.rows<<endl;

    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      g->bitmap.width,
      g->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      g->bitmap.buffer
    );

    float x2 = x + g->bitmap_left * sx;
    float y2 = -y - g->bitmap_top * sy;
    float w = g->bitmap.width * sx;
    float h = g->bitmap.rows * sy;

    cerr<<"bitmap_left:"<<g->bitmap_left<<endl;
    cerr<<"bitmap_top:"<<g->bitmap_top<<endl;

    cerr<<"x2:"<<x2<<endl;
    cerr<<"y2:"<<y2<<endl;
    cerr<<"x:"<<x<<endl;
    cerr<<"h:"<<h<<endl;
    cerr<<endl;

    x2=100/Video::getInstance()->getWidth();
    y2=100/Video::getInstance()->getHeight();
    w=200/Video::getInstance()->getWidth();
    h=50/Video::getInstance()->getHeight();

    GLfloat box[4][4] = {
        {x2,     -y2    , 0, 0},
        {x2 + w, -y2    , 1, 0},
        {x2,     -y2 - h, 0, 1},
        {x2 + w, -y2 - h, 1, 1},
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    x += (g->advance.x >> 6) * sx;
    y += (g->advance.y >> 6) * sy;
  }


  GTexture::getInstance()->setLastBind(NULL);
}


void TextManager::display()
{
    bool test2D=true;

    if(test2D)
        Video::getInstance()->matrixOrtho2D();

    //GLfloat black[4] = {0, 0, 0, 1};
    //glUniform4fv(uniform_color, 1, black);

    //glUseProgram(Video::getInstance()->programIDText);

    float sx =100;
    float sy =100;

    if(test2D)
    {
        sx=0.5;
        sy=0.5;
    }

    /*render_text("The Quick Brown Fox Jumps Over The Lazy Dog",
              -1 + 8 * sx,   1 - 50 * sy,    sx, sy);
    render_text("The Misaligned Fox Jumps Over The Lazy Dog",
              -1 + 8.5 * sx, 1 - 100.5 * sy, sx, sy);*/

    render_text("text3 ",100,100,100,100);


    if(test2D)
        Video::getInstance()->matrixProjection();

}










