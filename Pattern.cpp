#include "Pattern.h"
#include "GameObjects.h"





Pattern::Pattern()
{
    video=NULL;
    m_name="pattern";
}


void Pattern::start()
{
}

void Pattern::update(double functionTime)
{
    //check for pattern end
    //cerr<<"checking if "<<  m_lava->getPos().Z+m_lava->getSize().Z<<" >= "<<m_highestZ <<endl;
    if(m_lava->getPos().Z+m_lava->getSize().Z*2>=m_highestZ)
    {
        //cerr<<"pattern "<<m_name<<" finished!"<<endl;
        //cerr<<"lava level  "<<m_lava->getPos().Z+m_lava->getSize().Z*2<<" >"<<m_highestZ<<endl;
        m_finished=true;
    }
}

void Pattern::calculHighestZ()
{
    m_highestZ=0;
    for(unsigned int i=0,count=m_objects->size();i<count;i++)
    {
        if((*m_objects)[i]->getType()!="wall" && (*m_objects)[i]->getType()!="lava")
        {
            if((*m_objects)[i]->getPos().Z+(*m_objects)[i]->getSize().Z*2>m_highestZ)
                m_highestZ=(*m_objects)[i]->getPos().Z+(*m_objects)[i]->getSize().Z*2;
        }
    }
}

void Pattern::ini(double startZ, std::vector<Object*>* objects)
{
    m_startZ=startZ;
    m_objects=objects;


    //cerr<<"ini pattern "<<m_name<<". start Z is: "<<startZ <<endl;
    m_finished=false;

    //find walls and lava
    m_lava=NULL;
    m_walls.clear();
    for(unsigned int i=0,count=objects->size();i<count;i++)
    {
        if((*objects)[i]->getType()=="wall")
            m_walls.push_back((*objects)[i]);
        else if((*objects)[i]->getType()=="lava")
            m_lava=(*objects)[i];
    }



    m_highestZ=m_startZ;
    m_nextZ=-1;

    if(m_name!="pattern")
        loadPattern();

    if(m_highestZ==m_startZ)//if highest Z not specified in map file, calculate it
        calculHighestZ();
    if(m_nextZ==-1)
        m_nextZ=m_highestZ+5;
}

void Pattern::loadPattern()
{
    char* tempchemin=stringtochar("../data/patterns/"+m_name+".txt");
    cerr<<"loading pattern file "<< "../data/patterns/"<<m_name<<".txt" <<endl;

    std::ifstream in(tempchemin, std::ifstream::ate | std::ifstream::binary);
    int sizeMap=in.tellg();
    cerr<<"size map "<<tempchemin <<": "<<sizeMap<<endl;


    ifstream fichier1(tempchemin, ios::in);
    delete tempchemin;
    tempchemin=NULL;


    if(fichier1)
    {
        std::string befor_read="",read_name="",read_name_before="";
        std::string cur_read="";
        int curInt=0;
        int ind=-1;
        bool addingObject=false;

        while(!fichier1.eof())
        {
            //fichier1 >> cur_read;
            read_name=cur_read.substr(0,cur_read.size()-1);//enleve le ":"

            ind=(*m_objects).size();


            addingObject=addObjFromText(read_name,m_objects);

            if(addingObject)
            {
                (*m_objects)[ind]->readObj(&fichier1);
                (*m_objects)[ind]->setPos((*m_objects)[ind]->getPos()+Vector3D(0,0,m_startZ));
                (*m_objects)[ind]->setStartPos((*m_objects)[ind]->getPos());
                (*m_objects)[ind]->ini();

                //actually we dont want that one (walls)
                if((*m_objects)[ind]->getSize().Z>=1000)
                {
                    delete (*m_objects)[ind];
                    (*m_objects).pop_back();
                }
            }
            else if(read_name=="highestZ")
            {
                fichier1 >> curInt;
                m_highestZ=m_startZ+curInt;
            }
            else if(read_name=="nextZ")
            {
                fichier1 >> curInt;
                m_nextZ=m_startZ+curInt;
            }

            fichier1 >> cur_read;
            befor_read=cur_read;
            read_name_before=befor_read.substr(0,befor_read.size()-1);//enleve le ":"

        }

        fichier1.close();
    }
    else
        cerr << "can't open file (pattern file)" << endl;


}




