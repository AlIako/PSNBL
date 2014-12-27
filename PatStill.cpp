#include "PatStill.h"



PatStill::PatStill()
{
    m_name="still";
}


void PatStill::ini(double startZ, std::vector<Object*>* objects)
{
    Pattern::ini(startZ, objects);

    m_lavaspeed=0.1;
    m_fogdistancestart=100;
    m_fogdistanceend=300;
    m_fogr=0.0f;
    m_fogg=0.0f;
    m_fogb=0.0f;

    unsigned int ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(10,10,startZ+4));
    (*m_objects)[ind]->setSize(Vector3D(4,4,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(10,15,startZ+8));
    (*m_objects)[ind]->setSize(Vector3D(2,2,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(2,-50,startZ+2));
    (*m_objects)[ind]->setSize(Vector3D(50,10,8));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(50,2,startZ+18));
    (*m_objects)[ind]->setSize(Vector3D(10,50,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-50/1.5,-50/1.5,startZ+4));
    (*m_objects)[ind]->setSize(Vector3D(10,10,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-30,20,startZ+4));
    (*m_objects)[ind]->setSize(Vector3D(4,4,20));



    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(2,-40,startZ+40));
    (*m_objects)[ind]->setSize(Vector3D(1,10,1));




    ind=(*m_objects).size();
    (*m_objects).push_back(new Bonus());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->online=online;
    (*m_objects)[ind]->setName("rez");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(10,10,startZ+12.5));





    calculHighestZ();
}





