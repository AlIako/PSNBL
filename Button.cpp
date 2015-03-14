#include "Button.h"

Button::Button()
{
    m_clicable=false;
    m_hover=false;
    m_clicked=false;
    m_selected=false;

}

void Button::ini()
{
    setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/button_large.png"));

    m_shadow.setPos(m_position);
    m_shadow.setSize(m_size);
    GTexture::getInstance()->addTexture("../data/textures/interface/shadow.png");
    m_shadow.setTexture(GTexture::getInstance()->getTexture("../data/textures/interface/shadow.png"));

    text.setPos(m_position+Vector3D(m_size.X/2.0-text.getText().getSize()/100.0/2.0,m_size.Y/4.0,0));


    m_clicable=true;
}

void Button::draw()
{
    Object2D::draw();

    if(m_clicable && m_hover)
        m_shadow.draw();

    text.draw();
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


void Button::addText(string txt, freetype::font_data* font)
{
    text.addText(txt,font);
}





