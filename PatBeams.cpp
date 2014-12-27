#include "PatBeams.h"



PatBeams::PatBeams()
{
    m_name="PatBeams";
}

void PatBeams::ini(double startZ, std::vector<Object*>* objects)
{
    Pattern::ini(startZ, objects);

    m_lavaspeed=1;
    m_fogdistancestart=10;
    m_fogdistanceend=100;
    m_fogr=1.0f;
    m_fogg=0.0f;
    m_fogb=0.0f;

    //blocks
    double distBetwBeams=30;
    double zOffset=10;

    unsigned int ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(2,-30,startZ+zOffset+distBetwBeams*0));
    (*m_objects)[ind]->setSize(Vector3D(100,1,1));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(20,-30,startZ+zOffset+distBetwBeams*1));
    (*m_objects)[ind]->setSize(Vector3D(1,100,1));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(0,0,startZ+zOffset+distBetwBeams*2));
    (*m_objects)[ind]->setSize(Vector3D(100,1,1));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(0,0,startZ+zOffset+distBetwBeams*2));
    (*m_objects)[ind]->setSize(Vector3D(1,100,1));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(0,30,startZ+zOffset+distBetwBeams*3));
    (*m_objects)[ind]->setSize(Vector3D(100,1,1));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(30,30,startZ+zOffset+distBetwBeams*4));
    (*m_objects)[ind]->setSize(Vector3D(1,100,1));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-30,30,startZ+zOffset+distBetwBeams*5));
    (*m_objects)[ind]->setSize(Vector3D(100,1,1));




    calculHighestZ();
}




