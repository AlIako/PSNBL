#include "GameObjects.h"
#include "Block.h"
#include "Bonus.h"
#include "Flux.h"
#include "BossButan.h"
#include "Lava.h"
#include "Fogger.h"
#include "Fader.h"


bool addObjFromText(string txt, std::vector<Object*>* objects)
{
    bool isObj=false;
    if(txt=="block")
    {
        objects->push_back(new Block());
        isObj=true;
    }
    else if(txt=="bonus")
    {
        objects->push_back(new Bonus());
        isObj=true;
    }
    else if(txt=="flux")
    {
        objects->push_back(new Flux());
        isObj=true;
    }
    else if(txt=="boss")
    {
        objects->push_back(new BossButan());
        isObj=true;
    }
    else if(txt=="lava")
    {
        objects->push_back(new Lava());
        isObj=true;
    }
    else if(txt=="fogger")
    {
        objects->push_back(new Fogger());
        isObj=true;
    }
    else if(txt=="fader")
    {
        objects->push_back(new Fader());
        isObj=true;
    }
    return isObj;
}
