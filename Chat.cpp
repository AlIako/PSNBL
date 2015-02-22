#include "Chat.h"


Chat::Chat()
{
    m_writing=false;
    m_active=false;
    m_timeStay=5000;
    m_messages.clear();
    lastId=-1;
    up=true;
    m_side=0;//gauche
    gsounds=NULL;
    curseur=0;
}

void Chat::activate(int largeur, int hauteur, const char* t)
{
    m_largeur=largeur;
    m_hauteur=hauteur;
    m_active=true;
    m_font.init(t, 16);
    barre=new Texte();
    barre->ini(m_largeur,m_hauteur,&m_font);
    barre->setTexte("|");
    barre->setX(0.1);
    barre->setY(0.25);
    nextMessage.text=NULL;
}

void Chat::closeChat()
{
    delete barre;
    for(unsigned int i=0;i<m_messages.size();i++)
        delete m_messages[i].text;
    m_messages.clear();
}

void Chat::openTextBox(int iduser, double x)
{
    if(up)
    {
        barreA.reset();
        curuser=iduser;
        up=false;
        m_writing=true;
        nextMessage.msg="";
        curseur=0;
        barre->setX(x);
        barre->setY(0.25);
        if(nextMessage.text==NULL)
        {
            Texte* txt=new Texte();
            txt->ini(m_largeur,m_hauteur,&m_font);
            txt->setTexte("");
            txt->setX(x);
            txt->setY(0.35);
            nextMessage.text=txt;
        }
        SDL_EnableUNICODE( SDL_ENABLE );
    }
}
void Chat::openNeedString(string m,double x)
{
    ons=true;
    m_writing=true;
    nextMessage.msg=m;
    curseur=m.size();
    barre->setX(x);
    barre->setY(0.55);
    SDL_EnableUNICODE( SDL_ENABLE );
}
void Chat::closeTextBox()
{
    ons=false;
    m_writing=false;
    SDL_EnableUNICODE( SDL_DISABLE );
    nextMessage.text=NULL;
}
bool Chat::vide(string s)
{
    bool vide=true;
    for(unsigned int i=0;i<s.size();i++)
        if(s[i]!=' ')
            vide=false;

    return vide;
}
void Chat::enterUp()
{
    up=true;
}
void Chat::checkKeyboard()
{
    bool addChar=false;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
            m_writing=false;
            break;
            case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_RETURN:
                if(m_writing && up)
                {
                    up=false;
                    if(!ons && !vide(nextMessage.msg))
                    {
                        lastId++;
                        nextMessage.id=lastId;
                        nextMessage.apparu.reset();
                        nextMessage.user=curuser;
                        nextMessage.text->setTexte(nextMessage.msg);
                        m_messages.push_back(nextMessage);
                        msgToSend.push_back(nextMessage);
                        soundMsg();
                    }
                    closeTextBox();
                }
                break;
                case SDLK_LEFT:
                if(curseur>0) curseur--;
                break;
                case SDLK_RIGHT:
                if(curseur<nextMessage.msg.size()) curseur++;
                break;
                default:
                break;
            }
            addChar=false;
            if( event.key.keysym.unicode == (Uint16)' ' )
                addChar=true;
            else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
                addChar=true;
            else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
                addChar=true;
            else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
                addChar=true;
            else if( ( event.key.keysym.unicode >= (Uint16)':' ) && ( event.key.keysym.unicode <= (Uint16)'@' ) )
                addChar=true;
            else if( ( event.key.keysym.unicode >= (Uint16)'[' ) && ( event.key.keysym.unicode <= (Uint16)'_' ) )
                addChar=true;
            else if( ( event.key.keysym.unicode >= (Uint16)'!' ) && ( event.key.keysym.unicode <= (Uint16)'/' ) )
                addChar=true;
            if(addChar)
            {
                string m="";
                for(unsigned int i=0;i<curseur;i++)
                    m+=nextMessage.msg[i];
                m+=(char)event.key.keysym.unicode;
                for(unsigned int i=curseur;i<nextMessage.msg.size();i++)
                    if(i>=curseur)
                        m+=nextMessage.msg[i];
                nextMessage.msg=m;

                curseur++;
            }
            break;
            case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
                case SDLK_RETURN:
                up=true;
                break;
                case SDLK_ESCAPE:
                break;
                case SDLK_BACKSPACE:
                if(nextMessage.msg.size()>0 && curseur>0)
                {
                    string m=nextMessage.msg.substr(0,curseur-1);
                    m+=nextMessage.msg.substr(curseur,nextMessage.msg.size()-1);
                    nextMessage.msg=m;

                    curseur--;
                }
                break;
                default:
                break;
            }
            break;
            default:
            break;
        }
    }
}

void Chat::update()
{
}

bool Chat::possedeId(int id,int iduser)
{
    bool p=false;
    for(unsigned int i=0;i<m_messages.size();i++)
        if(m_messages[i].id==id && m_messages[i].user==iduser)
            p=true;
    return p;
}

void Chat::newMessage(string m, int iduser)
{
    lastId++;
    message newMSG;
    newMSG.id=lastId;
    newMSG.text=new Texte();
    newMSG.text->ini(m_largeur,m_hauteur,&m_font);
    newMSG.user=iduser;
    newMSG.text->setTexte(m);
    newMSG.apparu.reset();
    newMSG.msg=m;
    m_messages.push_back(newMSG);
    msgToSend.push_back(newMSG);

    soundMsg();
}
void Chat::recieveMessage(const char* t, int id, int iduser)
{
    if(!possedeId(id,iduser) ||true)
    {
        lastId++;
        message incMSG;
        incMSG.id=id;
        incMSG.text=new Texte();
        incMSG.text->ini(m_largeur,m_hauteur,&m_font);
        incMSG.user=iduser;
        incMSG.text->setTexte(t);
        incMSG.apparu.reset();
        m_messages.push_back(incMSG);

        soundMsg();
    }
}
void Chat::soundMsg()
{
    lastson.couler();
    if(gsounds!=NULL && lastson.ecouler(500))
    {
        lastson.reset();
        gsounds->play("data/sounds/chat.wav");
    }
}
void Chat::redrawAll()
{
    for(unsigned int i=0;i<m_messages.size();i++)
        m_messages[i].apparu.reset();
}
void Chat::draw()
{
    if(m_active)
    {
        glDisable(GL_DEPTH_TEST);
        glColor4ub(255,255,255,255);
        int compteur=0;
        for(int i=m_messages.size()-1;i>=0;i--)
        {
            compteur++;
            m_messages[i].apparu.couler();
            if(!m_messages[i].apparu.ecouler(10000))
            {
                if(m_side==0)//gauche
                    m_messages[i].text->setX(0.1);
                else if(m_side==1)//droite
                    m_messages[i].text->setX(0.25);
                m_messages[i].text->setY(0.3+compteur*0.05);

                int modul=5;
                if(m_messages[i].user%modul==0)
                    m_messages[i].text->draw(150,150,255);
                else if(m_messages[i].user%modul==1)
                    m_messages[i].text->draw(50,150,255);
                else if(m_messages[i].user%modul==2)
                    m_messages[i].text->draw(150,50,255);
                else if(m_messages[i].user%modul==3)
                    m_messages[i].text->draw(50,50,255);
                else if(m_messages[i].user%modul==4)
                    m_messages[i].text->draw(150,0,255);
                else if(m_messages[i].user%modul==5)
                    m_messages[i].text->draw(0,150,255);
                else if(m_messages[i].user==-2)//server
                    m_messages[i].text->draw(255,127,39);
                else//user
                    m_messages[i].text->draw(255,255,255);
            }
        }
        if(m_writing)
        {
            barreA.couler();
            if(barreA.ecouler(1000))
                barreA.reset();
            string m="";
            for(unsigned int i=0;i<curseur && i<nextMessage.msg.size();i++)
                m+=nextMessage.msg[i];
            if(!barreA.ecouler(500))
                m+="|";
            else m+=" ";
            for(unsigned int i=curseur;i<nextMessage.msg.size();i++)
                if(i>=curseur)
                    m+=nextMessage.msg[i];
            barre->setTexte(m);
            barre->draw(255,255,255);
        }
        glEnable(GL_DEPTH_TEST);
    }
}
void Chat::setSide(int side)
{
    m_side=side;
}
bool Chat::boxOpened()
{
    return m_writing;
}

bool Chat::active()
{
    return m_active;
}

