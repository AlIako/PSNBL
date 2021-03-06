#include "Object.h"
#define CD_LOSE_LIFE 100


Object::Object()
{
    m_position=Vector3D(0,0,0);
    m_rotation=Vector3D(0,0,0);
    m_velocity=Vector3D(0,0,0);
    m_direction=Vector3D(0,0,0);
    m_size=Vector3D(.5,.5,.5);
    m_type="object";
    m_name="name";
    m_speed=0.01;

    m_gravity=true;
    m_physical=false;

    m_selected=false;
    m_transparency=false;
    m_block=true;
    m_destructible=false;
    m_life=100;
    m_lifeMax=100;

    m_hookable=false;

    m_collided=false;
    ft=0;

    m_idOnline=-1;
    m_onlineName="unnamed";

    m_onTopOf=NULL;

    m_texture=NULL;

    m_active=true;

    m_visible=true;
    m_blur=false;

    time_since_ini.reset();
}

void Object::resurrect()
{
    m_life=4;
    m_position=Vector3D(0,0,40);
    m_rotation=Vector3D(0,0,0);
    m_velocity=Vector3D(0,0,0);
    m_colliding.clear();
}

void Object::loseLife(double value)
{
    last_lose_life.couler();
    if(last_lose_life.ecouler(CD_LOSE_LIFE))
    {
        last_lose_life.reset();
        m_life-=value;
    }
}

void Object::action(int type, Vector3D v)
{

}

void Object::action(int type, Object* o)
{

}


void Object::update(double functionTime)
{
    ft=functionTime;

    time_since_ini.couler();

    //kill if out of map
    //if(m_position.Z<=-50)
    //    m_life=0;


    bool wasOnTop=false;
    if(m_onTopOf!=NULL)
    {
        wasOnTop=true;
        //m_onTopOf->setVisible(true);
        m_onTopOf=NULL;
    }
    if(m_collided)
    {
        m_collided=false;
        for(unsigned int i=0, count=m_colliding.size();i<count;i++)
        {
            if(m_colliding[i]->getType()=="lava")
            {
                if(getDestructible())
                {
                    loseLife(3);
                }
            }
            else if(m_colliding[i]->getType()=="block")
            {
                if(m_colliding[i]->getPos().Z+m_colliding[i]->getSize().Z*2<=m_position.Z)
                {
                    m_onTopOf=m_colliding[i];

                    if(!wasOnTop)//landing -> stop Z velocity
                        m_velocity.Z=0;
                    //m_onTopOf->setVisible(false);
                }
            }
        }
        m_colliding.clear();
    }
}

void Object::moveToDir()
{
    //m_position+=m_direction*m_speed*ft;
    m_velocity=m_direction*m_speed*ft;
}

void Object::ini()
{
    time_since_ini.reset();
    //cerr <<"ini "<<m_type<<endl;
}

void Object::draw()
{

}

void Object::applyGravity()
{
    if(m_physical && m_gravity)
    {
        m_velocity.Z-=0.01*ft;
    }
}

void Object::drawBlur()
{

}

void Object::applyPhysics()
{
    applyPhysics(1,1,1);
}


void Object::applyPhysics(int x, int y, int z)
{
    if(x)
        m_position.X+=m_velocity.X+m_movementVelocity.X;
    if(y)
        m_position.Y+=m_velocity.Y+m_movementVelocity.Y;
    /*if(x)
        m_position.X+=m_velocity.X;
    if(y)
        m_position.Y+=m_velocity.Y;*/
    /*if(x)
        m_position.X+=m_velocity.X*m_movementVelocity.X;
    if(y)
        m_position.Y+=m_velocity.Y*m_movementVelocity.Y;*/


    if(z)
        m_position.Z+=m_velocity.Z;
}


void Object::rotaZDir()
{
    Vector3D dir2D=Vector3D(m_direction.X,m_direction.Y,0);
    m_rotation.Z=acos(dir2D.X/dir2D.length())*180/3.14;

    if(sin(dir2D.Y/dir2D.length())<0)
        m_rotation.Z*=-1;
}

bool Object::collidedWithType(std::string t)
{
    for(unsigned int i=0,count=m_colliding.size();i<count;i++)
    {
        if(m_colliding[i]->getType()==t)
            return true;
    }
    return false;
}
bool Object::collidedWithHookable()
{
    for(unsigned int i=0,count=m_colliding.size();i<count;i++)
    {
        if(m_colliding[i]->isHookable())
            return true;
    }
    return false;
}


bool Object::collision(Object* o)
{
    double marge=0.2*0;
    Vector3D m_taille_col=m_size;
    m_taille_col.X-=marge;
    m_taille_col.Y-=marge;
    m_taille_col.Z-=marge;

    Vector3D m_taille_colB=o->getSize();
    m_taille_colB.X-=marge;
    m_taille_colB.Y-=marge;
    m_taille_colB.Z-=marge;

    if(m_position.X-m_taille_col.X<o->getPos().X+m_taille_colB.X && m_position.X+m_taille_col.X>o->getPos().X-m_taille_colB.X &&
       m_position.Y-m_taille_col.Y<o->getPos().Y+m_taille_colB.Y && m_position.Y+m_taille_col.Y>o->getPos().Y-m_taille_colB.Y &&
       m_position.Z<o->getPos().Z+2*m_taille_colB.Z&& m_position.Z+2*m_taille_col.Z>o->getPos().Z)
        return true;
    /*if(m_position.X-m_taille_col.X<o->getPos().X+m_taille_colB.X && m_position.X+m_taille_col.X>o->getPos().X-m_taille_colB.X &&
       m_position.Y-m_taille_col.Y<o->getPos().Y+m_taille_colB.Y && m_position.Y+m_taille_col.Y>o->getPos().Y-m_taille_colB.Y &&
       m_position.Z<o->getPos().Z+2*m_taille_colB.Z&& m_position.Z+2*m_taille_col.Z>o->getPos().Z)
        return true;*/
    return false;
}


bool Object::onGround()
{
    return m_onTopOf!=NULL;
}



void Object::drawBox()
{
    glDisable(GL_TEXTURE_2D);
    Lighting::getInstance()->glDisableLighting();

    glColor3ub(255,0,0);
    glPushMatrix();
    glTranslated(m_position.X,m_position.Y,m_position.Z+m_size.Z);
    glBegin(GL_LINES);
    glVertex3d(-m_size.X,-m_size.Y,-m_size.Z);
    glVertex3d(m_size.X,-m_size.Y,-m_size.Z);
    glVertex3d(-m_size.X,-m_size.Y,-m_size.Z);
    glVertex3d(-m_size.X,m_size.Y,-m_size.Z);
    glVertex3d(m_size.X,-m_size.Y,-m_size.Z);
    glVertex3d(m_size.X,m_size.Y,-m_size.Z);
    glVertex3d(-m_size.X,m_size.Y,-m_size.Z);
    glVertex3d(m_size.X,m_size.Y,-m_size.Z);
    glVertex3d(-m_size.X,-m_size.Y,m_size.Z);
    glVertex3d(m_size.X,-m_size.Y,m_size.Z);
    glVertex3d(-m_size.X,-m_size.Y,m_size.Z);
    glVertex3d(-m_size.X,m_size.Y,m_size.Z);
    glVertex3d(m_size.X,-m_size.Y,m_size.Z);
    glVertex3d(m_size.X,m_size.Y,m_size.Z);
    glVertex3d(-m_size.X,m_size.Y,m_size.Z);
    glVertex3d(m_size.X,m_size.Y,m_size.Z);

    glVertex3d(-m_size.X,-m_size.Y,-m_size.Z);
    glVertex3d(-m_size.X,-m_size.Y,m_size.Z);
    glVertex3d(-m_size.X,m_size.Y,-m_size.Z);
    glVertex3d(-m_size.X,m_size.Y,m_size.Z);
    glVertex3d(m_size.X,-m_size.Y,-m_size.Z);
    glVertex3d(m_size.X,-m_size.Y,m_size.Z);
    glVertex3d(m_size.X,m_size.Y,-m_size.Z);
    glVertex3d(m_size.X,m_size.Y,m_size.Z);

    glEnd();
    glPopMatrix();
    glColor3ub(255,255,255);
    Lighting::getInstance()->glEnableLighting();
    glEnable(GL_TEXTURE_2D);

}

void Object::setButtons(vector<Button>* v,bool clear)
{
    if(clear)
        v->clear();
    int ind=0;
    v->push_back(Button());
    ind=v->size()-1;
    (*v)[ind].addText(m_type);
    (*v)[ind].setPos(Vector3D(-0.5,0.9,0));
    (*v)[ind].ini();
    (*v)[ind].setTexture(NULL);
    (*v)[ind].centerText(false);
    v->push_back(Button());
    ind=v->size()-1;
    (*v)[ind].addText("position: ");
    (*v)[ind].setName("position");
    (*v)[ind].needwhat="vector";
    (*v)[ind].addAuTexte(m_position);
    (*v)[ind].vec_change=&m_position;
    (*v)[ind].setPos(Vector3D(0.1,0.75,0));
    (*v)[ind].ini();
    (*v)[ind].centerText(false);
    (*v)[ind].setTexture(NULL);
    v->push_back(Button());
    ind=v->size()-1;
    (*v)[ind].addText("taille: ");
    (*v)[ind].setName("taille");
    (*v)[ind].needwhat="vector";
    (*v)[ind].addAuTexte(m_size);
    (*v)[ind].vec_change=&m_size;
    (*v)[ind].setPos(Vector3D(0.1,0.7,0));
    (*v)[ind].ini();
    (*v)[ind].setTexture(NULL);
    (*v)[ind].centerText(false);
    v->push_back(Button());
    ind=v->size()-1;
    (*v)[ind].addText("physical: ");
    (*v)[ind].setName("physical");
    (*v)[ind].addAuTexte(m_physical);
    (*v)[ind].setPos(Vector3D(0.1,0.65,0));
    (*v)[ind].ini();
    (*v)[ind].setTexture(NULL);
    (*v)[ind].centerText(false);
    v->push_back(Button());
    ind=v->size()-1;
    (*v)[ind].addText("block: ");
    (*v)[ind].setName("block");
    (*v)[ind].addAuTexte(m_block);
    (*v)[ind].setPos(Vector3D(0.1,0.55,0));
    (*v)[ind].ini();
    (*v)[ind].setTexture(NULL);
    (*v)[ind].centerText(false);
    v->push_back(Button());
    ind=v->size()-1;
    (*v)[ind].addText("texture: ");
    (*v)[ind].setName("texture");
    if(m_texture!=NULL)
        (*v)[ind].addAuTexte(m_texture->getChemin());
    else (*v)[ind].addAuTexte("N/A");
    (*v)[ind].setPos(Vector3D(0.1,0.5,0));
    (*v)[ind].ini();
    (*v)[ind].setTexture(NULL);
    (*v)[ind].centerText(false);
    /*
    v->push_back(Bouton());
    ind=v->size()-1;
    (*v)[ind].texte="rota z: ";
    (*v)[ind].needwhat="double";
    (*v)[ind].dou_change=&m_rz;
    (*v)[ind].addAuTexte(m_rz);
    (*v)[ind].m_x=0.1;
    (*v)[ind].m_y=0.45;*/
    v->push_back(Button());
    ind=v->size()-1;
    (*v)[ind].addText("rotation: ");
    (*v)[ind].setName("rotation");
    (*v)[ind].needwhat="vector";
    (*v)[ind].vec_change=&m_rotation;
    (*v)[ind].addAuTexte(m_rotation);
    (*v)[ind].setPos(Vector3D(0.1,0.45,0));
    (*v)[ind].ini();
    (*v)[ind].setTexture(NULL);
    (*v)[ind].centerText(false);
    v->push_back(Button());
    ind=v->size()-1;
    (*v)[ind].addText("visible: ");
    (*v)[ind].setName("visible");
    (*v)[ind].addAuTexte(m_visible);
    (*v)[ind].setPos(Vector3D(0.1,0.4,0));
    (*v)[ind].ini();
    (*v)[ind].setTexture(NULL);
    (*v)[ind].centerText(false);


    //mettre le bouton Ok en dessous des autres
    double m_miny=1;
    for(unsigned int i=0;i<v->size();i++)
        if((*v)[i].getPos().Y<m_miny)
            m_miny=(*v)[i].getPos().Y;

    v->push_back(Button());
    ind=v->size()-1;
    (*v)[ind].addText("OK");
    (*v)[ind].setPos(Vector3D(-0.5,m_miny-0.05,0));
    (*v)[ind].ini();
    (*v)[ind].setTexture(NULL);
    (*v)[ind].centerText(false);
}

void Object::checkClicks(vector<Button>* v,unsigned int id)
{
    if((*v)[id].getTxt().find("physical: ")!=string::npos)
    {
        if(m_physical)
            m_physical=false;
        else m_physical=true;
        (*v)[id].setText("physical: ");
        (*v)[id].addAuTexte(m_physical);
    }
    else if((*v)[id].getTxt().find("block: ")!=string::npos)
    {
        if(m_block)
            m_block=false;
        else m_block=true;
        (*v)[id].setText("block: ");
        (*v)[id].addAuTexte(m_block);
    }
    else if((*v)[id].getTxt().find("visible: ")!=string::npos)
    {
        if(m_visible)
            m_visible=false;
        else m_visible=true;
        (*v)[id].setText("visible: ");
        (*v)[id].addAuTexte(m_visible);
    }
}
string Object::writeObj()
{

    std::ostringstream oss;

    //classe
    oss << "@ " << m_type << ":";

    //x
    if(m_position.X!=0)
        oss<<" x: " << m_position.X;

    //y
    if(m_position.Y!=0)
        oss<<" y: " << m_position.Y;

    //z
    if(m_position.Z!=0)
        oss<<" z: " << m_position.Z;

    //taille
    if(m_size.X==m_size.Y && m_size.X==m_size.Z)
        oss<<" t: " << m_size.X;
    else
    {
        if(m_size.X!=0.5)
            oss << " tx: " << m_size.X;
        if(m_size.Y!=0.5)
            oss << " ty: " << m_size.Y;
        if(m_size.Z!=0.5)
            oss << " tz: " << m_size.Z;
    }
    //active
    if(!m_active)
        oss<<" active: 0";
    //texture
    if(m_texture!=NULL)
        oss<<" text: " << m_texture->getChemin();
    //visible
    if(!m_visible)
        oss<<" visible: 0";

    return oss.str();
}


void Object::readObj(ifstream* fichier1)
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
        else if(read_name_before=="visible")
        {
            *fichier1 >> curInt;
            if(curInt==0)
                m_visible=false;
        }

        *fichier1 >> cur_read;
        befor_read=cur_read;
        read_name_before=befor_read.substr(0,befor_read.size()-1);//enleve le ":"
    }


    m_startPosition=m_position;
}







