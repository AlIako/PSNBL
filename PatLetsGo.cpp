#include "PatLetsGo.h"



PatLetsGo::PatLetsGo()
{
    m_name="PatLetsGo";
}

void PatLetsGo::ini(double startZ, std::vector<Object*>* objects)
{
    Pattern::ini(startZ, objects);

    //blocks
    double zOffset=10;

    unsigned int ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(25,0,startZ+zOffset+2));
    (*m_objects)[ind]->setSize(Vector3D(50,1,1));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    //(*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(48,12,startZ+zOffset));
    (*m_objects)[ind]->setSize(Vector3D(4,25,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(48,48,startZ+zOffset));
    (*m_objects)[ind]->setSize(Vector3D(12,12,6));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    //(*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(30,42,startZ+zOffset+12));
    (*m_objects)[ind]->setSize(Vector3D(6,6,3));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(18,42,startZ+zOffset+18));
    (*m_objects)[ind]->setSize(Vector3D(6,6,3));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    //(*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(6,42,startZ+zOffset+24));
    (*m_objects)[ind]->setSize(Vector3D(6,6,3));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-6,42,startZ+zOffset+30));
    (*m_objects)[ind]->setSize(Vector3D(6,6,3));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    //(*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-18,42,startZ+zOffset+36));
    (*m_objects)[ind]->setSize(Vector3D(6,6,3));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-30,42,startZ+zOffset+42));
    (*m_objects)[ind]->setSize(Vector3D(6,6,3));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    //(*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-42,42,startZ+zOffset+48));
    (*m_objects)[ind]->setSize(Vector3D(6,6,3));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-46,30,startZ+zOffset+54));
    (*m_objects)[ind]->setSize(Vector3D(6,6,3));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    //(*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-46,18,startZ+zOffset+60));
    (*m_objects)[ind]->setSize(Vector3D(6,6,3));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-46,6,startZ+zOffset+66));
    (*m_objects)[ind]->setSize(Vector3D(6,6,3));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    //(*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-46,0,startZ+zOffset+72));
    (*m_objects)[ind]->setSize(Vector3D(6,6,3));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-34,0,startZ+zOffset+78));
    (*m_objects)[ind]->setSize(Vector3D(6,6,3));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    //(*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-22,0,startZ+zOffset+84));
    (*m_objects)[ind]->setSize(Vector3D(6,6,3));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->setName("noHookBlock");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-10,0,startZ+zOffset+90));
    (*m_objects)[ind]->setSize(Vector3D(6,6,3));




    calculHighestZ();
}




