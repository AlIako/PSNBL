#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include "Personnage.h"
#include "Block.h"
#include <vector>


class Map
{
    public:
    Map();

    void ini();
    void draw();

    //public attributes
    Gtexture* gtext;

    private:
    std::vector<Object*> m_objects;

};


#endif // MAP_H_INCLUDED
