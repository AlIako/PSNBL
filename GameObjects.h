#ifndef GAMEOBJECTS_H_INCLUDED
#define GAMEOBJECTS_H_INCLUDED
#include "Object.h"

bool addObjFromText(string txt, std::vector<Object*>* objects);
Object* getObjFromText(string txt);


#endif // GAMEOBJECTS_H_INCLUDED
