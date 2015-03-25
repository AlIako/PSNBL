#include "Fader.h"
#include "Video.h"

Fader::Fader()
{
    m_type="fader";
    m_name="fader";
    m_block=false;
    m_physical=false;
    m_fadeIn=true;

    m_r=1;
    m_g=1;
    m_b=1;
}



void Fader::ini()
{

}


void Fader::draw()
{

}


void Fader::action(int type, Object* o)
{
    Video::getInstance()->getFade()->setR(m_r*255);
    Video::getInstance()->getFade()->setG(m_g*255);
    Video::getInstance()->getFade()->setB(m_b*255);


    if(m_fadeIn)
        Video::getInstance()->getFade()->startFadeIn();
    else
        Video::getInstance()->getFade()->startFadeOut();
}


string Fader::writeObj()
{

    std::ostringstream oss;

    oss << Block::writeObj();

    if(m_fadeIn==false)
        oss<<" fadein: 0";

    oss<<" r: " << m_r;
    oss<<" g: " << m_g;
    oss<<" b: " << m_b;

    return oss.str();
}


void Fader::readObj(ifstream* fichier1)
{
    std::string befor_read="",read_name_before="";
    std::string cur_read="";
    double cur_double=0;
    int curInt=0;

    int maxIteration=1000;

    while(befor_read!="@" && maxIteration>0)
    {
        maxIteration--;
        if(read_name_before=="x")
            *fichier1 >> m_position.X;
        else if(read_name_before=="y")
            *fichier1 >> m_position.Y;
        else if(read_name_before=="z")
            *fichier1 >> m_position.Z;
        else if(read_name_before=="t")
        {
            *fichier1 >> cur_double;
            setSize(Vector3D(cur_double,cur_double,cur_double));
        }
        else if(read_name_before=="tx")
        {
            *fichier1 >> cur_double;
            m_size.X=cur_double;
            if(m_type=="rock")
                setSize(Vector3D(m_size.X,m_size.X,m_size.X));
            else if(m_type=="cylindre")
                setSize(Vector3D(m_size.X,m_size.X,m_size.Z));
            else if(m_type=="cone")
                setSize(Vector3D(m_size.X,m_size.X,m_size.Z));
            setSize(Vector3D(m_size.X,m_size.Y,m_size.Z));
        }
        else if(read_name_before=="ty")
        {
            *fichier1 >> m_size.Y;
            setSize(Vector3D(m_size.X,m_size.Y,m_size.Z));
        }
        else if(read_name_before=="tz")
        {
            *fichier1 >> m_size.Z;
            setSize(Vector3D(m_size.X,m_size.Y,m_size.Z));
        }
        else if(read_name_before=="text")
        {
            *fichier1 >> cur_read;
            GTexture::getInstance()->addTexture(cur_read);
            setTexture(GTexture::getInstance()->getTexture(cur_read));
        }
        else if(read_name_before=="name")
        {
            *fichier1 >> m_name;
        }
        else if(read_name_before=="active")
        {
            *fichier1 >> curInt;
            if(curInt==0)
                m_active=0;
        }
        else if(read_name_before=="text")
        {
            *fichier1 >> cur_read;
            m_texture=GTexture::getInstance()->addGetTexture(cur_read);
        }
        else if(read_name_before=="fadein:")
        {
            *fichier1 >> curInt;
            if(curInt==0)
                m_fadeIn=false;
        }
        else if(read_name_before=="r")
        {
            *fichier1 >> m_r;
        }
        else if(read_name_before=="g")
        {
            *fichier1 >> m_g;
        }
        else if(read_name_before=="b")
        {
            *fichier1 >> m_b;
        }

        *fichier1 >> cur_read;
        befor_read=cur_read;
        read_name_before=befor_read.substr(0,befor_read.size()-1);//enleve le ":"
    }


    m_startPosition=m_position;
}
