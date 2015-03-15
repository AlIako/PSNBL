#include "Texte.h"


Texte::Texte()
{
    m_largeur=640;
    m_hauteur=480;
    m_x=0;
    m_y=0;
    m_texte=" ";
    m_texture=NULL;
    m_font=NULL;
    m_taille=1;
    m_rota=0;
    m_alpha=255;
}

void Texte::ini(int largeur, int hauteur,freetype::font_data* font)
{
    m_largeur=largeur;
    m_hauteur=hauteur;
    m_font=font;
    if(m_x==-0.5)
    {
        m_x=0.5-m_texte.length()*13.0/largeur/3.0;
    }
}
void Texte::ini(int largeur, int hauteur)
{
    m_largeur=largeur;
    m_hauteur=hauteur;
    if(m_x==-0.5)
    {
        m_x=0.5-m_texte.length()*13.0/largeur/3.0;
    }
}

void Texte::setTexte(std::string t)
{
    m_texte=t+" ";
}
int Texte::getSize()
{
    return m_texte.size()-1;
}
void Texte::draw(int r, int g, int b)
{
    bool newLib=false;

    if(newLib)
    {
        TextManager::getInstance()->display();
    }
    else
    {
        glDisable(GL_CULL_FACE);
        glMatrixMode(GL_PROJECTION );
        glLoadIdentity( );
        gluOrtho2D(-m_largeur,m_largeur,-m_hauteur,m_hauteur);
        glMatrixMode( GL_MODELVIEW );
        glPushMatrix();
        glLoadIdentity( );
        glScalef(m_taille*m_largeur/640.00,m_taille*m_hauteur/480.00,1);
        glColor4ub(r,g,b,m_alpha);
        if(m_font!=NULL)
        {
            std::size_t found = m_texte.find("#");
            if(found!=std::string::npos)//sauts de lignes
            {
                string toprint="";
                int nbligne=0;
                bool nextdoi=false;
                for(unsigned int i=0;i<m_texte.length();i++)
                {
                    if(m_texte[i]!='#')
                    {
                        if(!nextdoi)
                            toprint+=m_texte[i];
                        else nextdoi=false;
                    }
                    else if(m_texte[i]=='#')
                    {
                        freetype::print(*m_font, m_x*m_largeur, (m_y-nbligne/20.00)*m_hauteur, toprint, m_largeur, m_hauteur);
                        nbligne++;
                        nextdoi=true;
                        toprint.clear();;
                    }
                }
                if(toprint!="")
                    freetype::print(*m_font, m_x*m_largeur, (m_y-nbligne/20.00)*m_hauteur, toprint, m_largeur, m_hauteur);
            }
            else
                freetype::print(*m_font, m_x*m_largeur, m_y*m_hauteur, m_texte, m_largeur, m_hauteur);
        }

        glPopMatrix();
        Video::getInstance()->matrixProjection();

        //si on affiche une texture
        if(m_texture!=NULL)
        {
            glDisable(GL_LIGHTING);
            int posx=(m_x-0.05)*m_largeur;
            if(m_texte.size()==0)
                posx=m_x*m_largeur;
            int posy=m_y*m_hauteur;
            m_texture->bind(true);
            //dessiner ptit carré avec la texture
            glMatrixMode(GL_PROJECTION );
            glLoadIdentity( );
            gluOrtho2D(0,m_largeur,0,m_hauteur);
            glMatrixMode( GL_MODELVIEW );
            glLoadIdentity( );
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glPushMatrix();
            glTranslated(posx,posy,0);
            glScalef(m_largeur/640.00,m_hauteur/480.00,1);
            glRotated(m_rota,0,0,1);
            int tailleCarre=30;
            if(m_rota>0)
            {
                glBegin(GL_QUADS);
                glTexCoord2d(1,0);    glVertex2d(-tailleCarre/2,-tailleCarre/2);
                glTexCoord2d(1,1);    glVertex2d(-tailleCarre/2,tailleCarre/2);
                glTexCoord2d(0,1);    glVertex2d(tailleCarre/2,tailleCarre/2);
                glTexCoord2d(0,0);    glVertex2d(tailleCarre/2,-tailleCarre/2);
                glEnd();
            }
            else
            {
                glBegin(GL_QUADS);
                glTexCoord2d(1,0);    glVertex2d(0,0);
                glTexCoord2d(1,1);    glVertex2d(0,tailleCarre);
                glTexCoord2d(0,1);    glVertex2d(tailleCarre,tailleCarre);
                glTexCoord2d(0,0);    glVertex2d(tailleCarre,0);
                glEnd();
            }
            glRotated(-m_rota,0,0,1);
            glPopMatrix();
            glDisable(GL_BLEND);

            Video::getInstance()->matrixProjection();
            glEnable(GL_LIGHTING);
        }
        glEnable(GL_CULL_FACE);
        glDisable(GL_CULL_FACE);
    }
}

void Texte::setX(float x)
{
    m_x=x;
}

void Texte::setY(float y)
{
    m_y=y;
}
void Texte::setTaille(float t)
{
    m_taille=t;
}
void Texte::setRota(float r)
{
    m_rota=r;
}
void Texte::setAlpha(float a)
{
    m_alpha=a;
}

void Texte::move(float x, float y)
{
    m_x+=x;
    m_y+=y;
}

float Texte::getX()
{
    return m_x;
}

float Texte::getY()
{
    return m_y;
}

void Texte::killFont()
{
    if(m_font!=NULL)
    {
        //m_font->clean();
        //delete m_font;
    }
}
Texte::~Texte()
{
    //killFont();
}



