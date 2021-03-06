#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include "Object2D.h"

class Button: public Object2D
{
    public:
        Button();

        virtual void ini();

        void draw();
        void update(double functionTime);

        void updateCursor(Vector3D pos);
        bool clic(Vector3D pos);

        virtual void addText(string txt);
        virtual void setText(string txt);
        void centerText(bool c);

        void setClicable(bool c){m_clicable=c;}
        void setHover(bool h){m_hover=h;}
        void setSelectable(bool s){m_selectable=s;}
        void select(bool s);
        void translate(double x, double y);

        bool getClicable(){return m_clicable;}
        bool isSelected(){return m_selected;}

        void addAuTexte(int v, bool delprec=true);
        void addAuTexte(double v, bool delprec=true);
        void addAuTexte(string v, bool delprec=true);
        void addAuTexte(Vector3D v, bool delprec=true);
        void applyChangesVariable(string s);
        void applyChangesVariable(double d);
        void applyChangesVariable(int i);
        void applyChangesVariable(Vector3D v);

        string getTxt(){return text.getText().getTexte();}


        Object2D text;
        string needwhat;
        string* str_change;
        double* dou_change;
        int* int_change;
        Vector3D* vec_change;


    private:
        Object2D m_shadow;

        bool m_clicable;
        bool m_hover;
        bool m_selectable;
        bool m_selected;
};


#endif // BUTTON_H_INCLUDED
