#ifndef PATTERN_H_INCLUDED
#define PATTERN_H_INCLUDED
#include "Block.h"
#include "Bonus.h"
#include "Video.h"

class Pattern
{
    public:
    Pattern();

    virtual void update(double functionTime);

    virtual void ini(double startZ, std::vector<Object*>* objects);
    virtual void start();

    void calculHighestZ();
    double getHighestZ() {return m_highestZ;}
    double getStartZ() {return m_startZ;}
    int getPID();
    bool finished() {return m_finished;}

    void setStartZ(double s) {m_startZ=s;}

    //public attributes
    GTexture* gtext;
    Video *video;
    Online* online;

    protected:
    std::string m_name;
    std::vector<Object*>* m_objects;
    Object* m_lava;
    std::vector<Object*> m_walls;

    bool m_finished;

    double m_fogdistancestart;
    double m_fogdistanceend;
    float m_fogr;
    float m_fogg;
    float m_fogb;

    double m_lavaspeed;
    double m_startZ;
    double m_highestZ;
};

#endif // PATTERN_H_INCLUDED
