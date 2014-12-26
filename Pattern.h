#ifndef PATTERN_H_INCLUDED
#define PATTERN_H_INCLUDED
#include "Block.h"

class Pattern
{
    public:
    Pattern();

    virtual void update(double functionTime);

    virtual void ini(double startZ, std::vector<Object*>* objects);
    virtual void start();

    void calculHighestZ();
    double getHighestZ() {return m_highestZ;}

    bool finished() {return m_finished;}

    //public attributes
    GTexture* gtext;

    protected:
    std::string m_name;
    std::vector<Object*>* m_objects;
    Object* m_lava;
    std::vector<Object*> m_walls;

    bool m_finished;

    double m_lavaspeed;
    double m_startZ;
    double m_highestZ;
};

#endif // PATTERN_H_INCLUDED
