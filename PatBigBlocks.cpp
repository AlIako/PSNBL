#include "PatBigBlocks.h"



PatBigBlocks::PatBigBlocks()
{
    m_name="PatBigBlocks";
}

void PatBigBlocks::ini(double startZ, std::vector<Object*>* objects)
{
    Pattern::ini(startZ, objects);

    //blocks

    unsigned int ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(10,-20,startZ+10));
    (*m_objects)[ind]->setSize(Vector3D(8,8,12));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-10,-30,startZ+30));
    (*m_objects)[ind]->setSize(Vector3D(8,8,12));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(10,0,startZ+40));
    (*m_objects)[ind]->setSize(Vector3D(8,8,12));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-10,30,startZ+60));
    (*m_objects)[ind]->setSize(Vector3D(8,8,12));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-10,-30,startZ+80));
    (*m_objects)[ind]->setSize(Vector3D(8,8,12));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(10,0,startZ+100));
    (*m_objects)[ind]->setSize(Vector3D(8,8,12));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-10,30,startZ+120));
    (*m_objects)[ind]->setSize(Vector3D(8,8,12));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-10,-30,startZ+140));
    (*m_objects)[ind]->setSize(Vector3D(8,8,12));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(10,0,startZ+160));
    (*m_objects)[ind]->setSize(Vector3D(8,8,12));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-10,30,startZ+180));
    (*m_objects)[ind]->setSize(Vector3D(8,8,12));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-10,-30,startZ+200));
    (*m_objects)[ind]->setSize(Vector3D(8,8,12));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(10,0,startZ+220));
    (*m_objects)[ind]->setSize(Vector3D(8,8,12));

    ind=(*m_objects).size();
    (*m_objects).push_back(new Block());
    (*m_objects)[ind]->gtext=gtext;
    (*m_objects)[ind]->ini();
    (*m_objects)[ind]->setPos(Vector3D(-10,30,startZ+240));
    (*m_objects)[ind]->setSize(Vector3D(8,8,12));


    calculHighestZ();
}




