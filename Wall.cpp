#include "Wall.h"





Wall::Wall()
{
    mosaic=15;
    m_hookable=false;
}



void Wall::ini()
{
    m_type="wall";
    if(gtext!=NULL)
    {
        gtext->addTexture("../data/textures/hellrock_static.png");
        m_texture=gtext->getTexture("../data/textures/hellrock_static.png");
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
