#include "Button.h"

Button::Button()
{
    m_clicable=false;
    m_hover=false;
    m_selectable=false;
    m_selected=false;
}

void Button::ini()
{
    setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_large.png"));

    m_shadow.setPos(m_position);
    m_shadow.setSize(m_size);
    GTexture::getInstance()->addTexture("../data/textures/interface/shadow.png");
    m_shadow.setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/shadow.png"));

    text.setPos(m_position+Vector3D(0,m_size.Y/4.0,0));
    centerText(true);

    m_clicable=true;

    //if size not set, use text size
    if(m_size.X==0.1 && m_size.Y==0.1)
    {
        m_size=Vector3D(text.getText().getTextWidth()/Video::getInstance()->getWidth(),0.05,0);
        m_shadow.setSize(m_size);
    }
}

void Button::draw()
{
    Object2D::draw();

    if(m_clicable)
    {
        if(m_selected)
        {
            text.setR(200);
            text.setG(50);
            text.setB(20);
        }
        else if(m_hover)
        {
            m_shadow.draw();
            text.setR(240);
            text.setG(85);
            text.setB(0);
        }
    }
    if(!m_clicable || (!m_hover && !m_selected))
    {
        text.setR(240);
        text.setG(182);
        text.setB(0);
    }

    text.draw();
}

void Button::select(bool s)
{
    if(m_selectable)
        m_selected=s;
}

void Button::update(double functionTime)
{

}

void Button::updateCursor(Vector3D pos)
{
    m_hover=false;
    if(clic(pos))
        m_hover=true;
}


bool Button::clic(Vector3D pos)
{
    //cerr<<"clic on: "<<pos.X<<", "<<pos.Y<<endl;

    //origin clic sdl: top left
    //origin sprite object2D: bot left

    pos.Y=Video::getInstance()->getHeight()-pos.Y;

    pos.X/=Video::getInstance()->getWidth();
    pos.Y/=Video::getInstance()->getHeight();
    //cerr<<"clic on: "<<pos.X<<", "<<pos.Y<<endl;

    if(pos.X>m_position.X && pos.X<m_position.X+m_size.X &&
       pos.Y>m_position.Y && pos.Y<m_position.Y+m_size.Y)
            return true;
    return false;
}

void Button::translate(double x,double y)
{
    m_position+=Vector3D(x,y,0);
    m_shadow.setPos(m_position);
    text.setPos(m_position+Vector3D(0,m_size.Y/4.0,0));
}

void Button::addText(string txt)
{
    text.addText(txt);
}


void Button::setText(string txt)
{
    text.setText(txt);
}

void Button::centerText(bool c)
{
    if(c)
        text.setPos(m_position+Vector3D(m_size.X/2.0-text.getText().getTextWidth()/2.0/Video::getInstance()->getWidth(),m_size.Y/4.0,0));
    else
        text.setPos(m_position+Vector3D(0,m_size.Y/4.0,0));
}



void Button::addAuTexte(int v, bool delprec)
{
    /*if(delprec)
        textefinal=texte;*/
    stringstream ss;
    ss << m_name <<": "<< v;
    text.setText(ss.str());
}
void Button::addAuTexte(double v, bool delprec)
{
    /*if(delprec)
        textefinal=texte;*/
    stringstream ss;
    ss << m_name <<": " << v;
    text.setText(ss.str());
}
void Button::addAuTexte(string v, bool delprec)
{
    /*if(delprec)
        textefinal=texte;*/
    stringstream ss;
    ss << m_name <<": " << v;
    text.setText(ss.str());
}
void Button::addAuTexte(Vector3D v, bool delprec)
{
    /*if(delprec)
        textefinal=texte;*/
    stringstream ss;
    ss << m_name <<": "  << v.X << ", " << v.Y << ", " << v.Z;
    text.setText(ss.str());
}

void Button::applyChangesVariable(string s)
{
    if(str_change!=NULL)
        *str_change=s;
    text.setText(m_name+": "+s);
}

void Button::applyChangesVariable(double d)
{
    if(dou_change!=NULL)
        *dou_change=d;
    addAuTexte(d);
    ini();
}

void Button::applyChangesVariable(int i)
{
    if(int_change!=NULL)
        *int_change=i;
    addAuTexte(i);
    ini();
}


void Button::applyChangesVariable(Vector3D v)
{
    if(vec_change!=NULL)
        *vec_change=v;
    addAuTexte(v);
    ini();
}


