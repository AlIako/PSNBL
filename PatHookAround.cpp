#include "PatHookAround.h"



PatHookAround::PatHookAround()
{
    m_name="PatHookAround";
}

void PatHookAround::ini(double startZ, std::vector<Object*>* objects)
{
    Pattern::ini(startZ, objects);

    //blocks
    double zOffset=10;
    double distBetwBlock=10;

    unsigned int ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(25,0,startZ+zOffset+2));
    (*m_objects)[ind]->setSize(Vector3D(50,1,1));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(46,0,startZ+zOffset+10+distBetwBlock));
    (*m_objects)[ind]->setSize(Vector3D(4,4,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(46,46,startZ+zOffset+10+distBetwBlock*2));
    (*m_objects)[ind]->setSize(Vector3D(4,4,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(0,46,startZ+zOffset+10+distBetwBlock*3));
    (*m_objects)[ind]->setSize(Vector3D(4,4,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-46,46,startZ+zOffset+10+distBetwBlock*4));
    (*m_objects)[ind]->setSize(Vector3D(4,4,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-46,0,startZ+zOffset+10+distBetwBlock*5));
    (*m_objects)[ind]->setSize(Vector3D(4,4,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-46,-46,startZ+zOffset+10+distBetwBlock*6));
    (*m_objects)[ind]->setSize(Vector3D(4,4,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(0,-46,startZ+zOffset+10+distBetwBlock*7));
    (*m_objects)[ind]->setSize(Vector3D(4,4,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(46,-46,startZ+zOffset+10+distBetwBlock*8));
    (*m_objects)[ind]->setSize(Vector3D(4,4,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(46,0,startZ+zOffset+10+distBetwBlock*9));
    (*m_objects)[ind]->setSize(Vector3D(4,4,4));




    calculHighestZ();
}




