#ifndef FOG_H_INCLUDED
#define FOG_H_INCLUDED
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

class Fog
{
    public:
    Fog();
    void update(double functionTime);

    void setTarget(double fogdistancestart,double fogdistanceend,float fogr,float fogg,float fogb);
    void setSpeedColor(double s){m_speedColor=s;}
    void setSpeedDistance(double s){m_speedDistance=s;}

    void enable();
    void disable();


    private:
    bool m_enabled;

    double m_speedColor;
    double m_speedDistance;

    //fog
    double m_fogdistancestart;
    double m_fogdistanceend;
    float m_fogr;
    float m_fogg;
    float m_fogb;

    double m_targetfogdistancestart;
    double m_targetfogdistanceend;
    float m_targetfogr;
    float m_targetfogg;
    float m_targetfogb;
};


#endif // FOG_H_INCLUDED
