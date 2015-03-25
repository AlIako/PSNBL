#include "Fog.h"




Fog::Fog()
{
    m_fogdistancestart=200;
    m_fogdistanceend=500;
    m_fogr=0.0f;
    m_fogg=0.0f;
    m_fogb=0.0f;

    m_targetfogdistancestart=m_fogdistancestart;
    m_targetfogdistanceend=m_fogdistanceend;
    m_targetfogr=0.0f;
    m_targetfogg=0.0f;
    m_targetfogb=0.0f;

    m_speedColor=0.001;
    m_speedDistance=1;

    m_enabled=false;
}


void Fog::update(double functionTime)
{
    if(m_enabled)
    {
        bool needUpdate=false;

        double colorStep=functionTime*m_speedColor;
        double distanceStep=functionTime*m_speedDistance;

        //distance
        if(m_targetfogdistancestart!=m_fogdistancestart)
        {
            m_fogdistancestart+=distanceStep*(m_targetfogdistancestart-m_fogdistancestart)/fabs(m_targetfogdistancestart-m_fogdistancestart);
            if(fabs(m_targetfogdistancestart-m_fogdistancestart)<distanceStep)
                m_fogdistancestart=m_targetfogdistancestart;

            needUpdate=true;
        }
        if(m_targetfogdistanceend!=m_fogdistanceend)
        {
            m_fogdistanceend+=distanceStep*(m_targetfogdistanceend-m_fogdistanceend)/fabs(m_targetfogdistanceend-m_fogdistanceend);
            if(fabs(m_targetfogdistanceend-m_fogdistanceend)<distanceStep)
                m_fogdistanceend=m_targetfogdistanceend;

            needUpdate=true;
        }

        //color
        if(m_targetfogr!=m_fogr)
        {
            m_fogr+=colorStep*(m_targetfogr-m_fogr)/fabs(m_targetfogr-m_fogr);
            if(fabs(m_targetfogr-m_fogr)<colorStep)
                m_fogr=m_targetfogr;

            needUpdate=true;
        }
        if(m_targetfogg!=m_fogg)
        {
            m_fogg+=colorStep*(m_targetfogg-m_fogg)/fabs(m_targetfogg-m_fogg);
            if(fabs(m_targetfogg-m_fogg)<colorStep)
                m_fogg=m_targetfogg;

            needUpdate=true;
        }
        if(m_targetfogb!=m_fogb)
        {
            m_fogb+=colorStep*(m_targetfogb-m_fogb)/fabs(m_targetfogb-m_fogb);
            if(fabs(m_targetfogb-m_fogb)<colorStep)
                m_fogb=m_targetfogb;

            needUpdate=true;
        }

        if(needUpdate)
        {
            //update fog
            glClearColor(m_fogr, m_fogg, m_fogb, 1.0f);
            glFogi(GL_FOG_MODE, GL_LINEAR);//GL_LINEAR,GL_EXP ou GL_EXP2
            glFogf(GL_FOG_START, m_fogdistancestart);
            glFogf(GL_FOG_END, m_fogdistanceend);
            GLfloat fog_c[] = {m_fogr, m_fogg, m_fogb, 1.0f};//couleur du brouillard, ici noir
            glFogfv(GL_FOG_COLOR, fog_c);
        }
    }
}



void Fog::setTarget(double fogdistancestart,double fogdistanceend,float fogr,float fogg,float fogb)
{
    m_targetfogdistancestart=fogdistancestart;
    m_targetfogdistanceend=fogdistanceend;
    m_targetfogr=fogr;
    m_targetfogg=fogg;
    m_targetfogb=fogb;
}




void Fog::enable()
{
    m_enabled=true;
    glClearColor(m_fogr, m_fogg, m_fogb, 1.0f);
    glFogi(GL_FOG_MODE, GL_LINEAR);//GL_LINEAR,GL_EXP ou GL_EXP2
    glFogf(GL_FOG_START, m_fogdistancestart);
    glFogf(GL_FOG_END, m_fogdistanceend);
    GLfloat fog_c[] = {m_fogr, m_fogg, m_fogb, 1.0f};//couleur du brouillard, ici noir
    glFogfv(GL_FOG_COLOR, fog_c);
    glEnable(GL_FOG);
}
void Fog::disable()
{
    m_enabled=false;
    glDisable(GL_FOG);
}

void Fog::close()
{
    setColor(0,0,0);
    setTarget(200,500,0,0,0);
    update(0);
}

