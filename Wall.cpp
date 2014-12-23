#include "Wall.h"





Wall::Wall()
{
    mosaic=10;
}



void Wall::ini()
{
    m_type="wall";
    if(gtext!=NULL)
    {
        gtext->addTexture("../data/textures/wall.jpg");
        m_texture=gtext->getTexture("../data/textures/wall.jpg");
    }

    Object::ini();
}


void Wall::draw()
{
    Block::draw();
}
