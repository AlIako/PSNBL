#ifndef TEXTE_H_INCLUDED
#define TEXTE_H_INCLUDED
#include <GL/glew.h>
#include <string>
#include "freetype.h"
#include "utilFunctions.h"
#include "Texture.h"
#include "Video.h"
#include "TextManager.h"

class Texte
{
    public:
    Texte();
    ~Texte();
    void ini(int largeur, int hauteur,freetype::font_data* font);
    void ini(int largeur, int hauteur);
    void setTexte(std::string t);
    int getSize();
    void draw(int r, int g, int b);
    void setX(float x);
    void setY(float y);
    void setTaille(float t);
    void setRota(float r);
    void setAlpha(float a);
    void move(float x, float y);
    float getX();
    float getY();
    void killFont();

    Texture* m_texture;
    private:


    freetype::font_data* m_font;
    std::string m_texte;
    int m_hauteur;
    int m_largeur;
    float m_x;
    float m_y;
    float m_taille;
    float m_rota;
    int m_alpha;
};


#endif // TEXTE_H_INCLUDED
