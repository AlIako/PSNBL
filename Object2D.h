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


        virtual void addText(string txt);
        virtual void setText(string txt);

        void setTexture(Texture* t){m_texture=t;}
        void setPos(Vector3D v) {m_position=v;}
        void setSize(Vector3D v) {m_size=v;}
        void setName(std::string s) {m_name=s;}
        void setR(int r){m_r=r;}
        void setG(int g){m_g=g;}
        void setB(int b){m_b=b;}
        void setAlpha(double a){m_alpha=a;}

        std::string getName() {return m_name;}
        Texte getText(){return m_text;}
        double getAlpha() {return m_alpha;}
        Texture* getTexture(){return m_texture;}

    protected:
        Texture* m_texture;

        Vector3D m_position;
        Vector3D m_size;

        std::string m_name;


        bool m_hasText;
        Texte m_text;

        double m_alpha;
        int m_r;
        int m_g;
        int m_b;
};



#endif // OBJECT2D_H_INCLUDED
