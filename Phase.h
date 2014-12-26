#ifndef PHASE_H_INCLUDED
#define PHASE_H_INCLUDED
#include "PatStill.h"
#include "PatBigBlocks.h"

class Phase
{
    public:
    Phase();

    void ini(std::vector<Object*>* objects);
    void iniMap();

    void update(double functionTime);

    void addPatternToQueue();
    void nextPattern();
    void goToNextPhase();

    void erase();

    //public attributes
    GTexture* gtext;

    private:
    std::string m_name;

    std::vector<Pattern*> m_patternQueue;
    Pattern* m_pattern;

    std::vector<Object*>* m_objects;
    Object* m_lava;
    std::vector<Object*> m_walls;

    double m_fogdistance;

    double highestZ;
};


#endif // PHASE_H_INCLUDED
