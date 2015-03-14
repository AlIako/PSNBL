#include "PatStill.h"



PatStill::PatStill()
{
    m_name="still";
}


void PatStill::ini(double startZ, std::vector<Object*>* objects)
{
    Pattern::ini(startZ, objects);

    unsigned int ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(10,10,startZ+4));
    (*m_objects)[ind]->setSize(Vector3D(4,4,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(10,15,startZ+8));
    (*m_objects)[ind]->setSize(Vector3D(2,2,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(2,-50,startZ+2));
    (*m_objects)[ind]->setSize(Vector3D(50,10,8));
    ind=(*m_objects).size();


    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(2,50,startZ+2));
    (*m_objects)[ind]->setSize(Vector3D(50,10,8));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(50,2,startZ+2));
    (*m_objects)[ind]->setSize(Vector3D(10,42,8));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-50,2,startZ+2));
    (*m_objects)[ind]->setSize(Vector3D(10,42,8));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-50/1.5,-50/1.5,startZ+4));
    (*m_objects)[ind]->setSize(Vector3D(10,10,4));


    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-30,20,startZ+4));
    (*m_objects)[ind]->setSize(Vector3D(4,4,20));


    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-30,-20,startZ+14));
    (*m_objects)[ind]->setSize(Vector3D(10,10,5));





    //to hook around
    /*ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(0,-20,startZ+40));
    (*m_objects)[ind]->setSize(Vector3D(2,2,4));*/

    /*ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(0,20,startZ+40));
    (*m_objects)[ind]->setSize(Vector3D(2,2,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(20,0,startZ+40));
    (*m_objects)[ind]->setSize(Vector3D(2,2,4));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-20,0,startZ+40));
    (*m_objects)[ind]->setSize(Vector3D(2,2,4));*/


    //bridge
    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(0,0,startZ+16));
    (*m_objects)[ind]->setSize(Vector3D(2,40,1));

    //bonus rez
    ind=(*m_objects).size();
    (*m_objects).push_back(new Bonus());
    (*m_objects)[ind]->setName("rez");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(0,0,startZ+18));
    //bonus nextphase
    ind=(*m_objects).size();
    (*m_objects).push_back(new Bonus());
    (*m_objects)[ind]->setName("nextphase");
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(0,0,startZ+18));


    calculHighestZ();
    m_highestZ-=25;
    m_highestZ=startZ+5;
    m_nextZ=m_highestZ+15;
}





