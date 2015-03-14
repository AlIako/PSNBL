#ifndef OBJECT2D_H_INCLUDED
#define OBJECT2D_H_INCLUDED
#include "Video.h"
#include "Vector3D.h"
#include "GTexture.h"
#include "Texte.h"
#include <vector>

class Object2D
{
    public:
        Object2D();
        void draw();
        void update(double functionTime);

        virtual void ini();


        virtual void addText(string txt, freetype::font_data* font);
        void setText(string txt);

        void setTexture(Texture* t){m_texture=t;}
        void setPos(Vector3D v) {m_position=v;}
        void setSize(Vector3D v) {m_size=v;}
        void setName(std::string s) {m_name=s;}

        std::string getName() {return m_name;}
        Texte getText(){return m_text;}

    protected:
        Texture* m_texture;

        Vector3D m_position;
        Vector3D m_size;

        std::string m_name;


        bool m_hasText;
        Texte m_text;
};



#endif // OBJECT2D_H_INCLUDED
