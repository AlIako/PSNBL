#include "GameObjects.h"
#include "Block.h"
#include "Bonus.h"
#include "Flux.h"
#include "BossButan.h"
#include "Lava.h"
#include "Fogger.h"
#include "Fader.h"
#include "Warninger.h"
#include "Lighter.h"


bool addObjFromText(string txt, std::vector<Object*>* objects)
{
    bool isObj=false;
    Object* willBeAdded=getObjFromText(txt);

    if(willBeAdded!=NULL)
    {
        isObj=true;
        objects->push_back(willBeAdded);
    }
    return isObj;
}
Object* getObjFromText(string txt)
{
    if(txt=="block")
        return new Block();
    else if(txt=="bonus")
        return new Bonus();
    else if(txt=="flux")
        return new Flux();
    else if(txt=="boss")
        return new BossButan();
    else if(txt=="lava")
        return new Lava();
    else if(txt=="fogger")
        return new Fogger();
    else if(txt=="fader")
        return new Fader();
    else if(txt=="warninger")
        return new Warninger();
    else if(txt=="lighter")
        return new Lighter();
    return NULL;
}
