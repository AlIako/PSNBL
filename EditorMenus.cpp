#include "Editor.h"






void Editor::menuObj()
{
    //unselect all; select concerned obj.
    for(unsigned int i=0;i<m_objects->size();i++)
    {
        if((int)i==objSelected)
            (*m_objects)[i]->select(true);
        else
            (*m_objects)[i]->select(false);
    }

    stringstream ss;
    ss<<"picking object id: "<<objSelected;
    Tracer::getInstance()->trace("editor",ss.str());
}








