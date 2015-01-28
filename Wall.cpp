#include "Wall.h"





Wall::Wall()
{
    mosaic=15;
    m_hookable=false;
}



void Wall::ini()
{
    m_type="wall";
    if(GTexture::getInstance()!=NULL)
    {
        GTexture::getInstance()->addTexture("../data/textures/hellrock_static.png");
        m_texture=GTexture::getInstance()->getTexture("../data/textures/hellrock_static.png");
    }

    Object::ini();

    m_r=255;
    m_g=255;
    m_b=255;

    m_hookable=false;
}


void Wall::draw()
{
    Block::draw();
}
