#ifndef PHASE_H_INCLUDED
#define PHASE_H_INCLUDED
#include "PatStill.h"
#include "PatBigBlocks.h"
#include "PatMidBlocks.h"
#include "PatBeams.h"
#include "PatEndPhase.h"
#include "PatLetsGo.h"
#include "PatHookAround.h"
#include "Online.h"

class Phase
{
    public:
    Phase();

    void ini(std::vector<Object*>* objects);
    void iniMap();
    void iniPhaseProperties();

    void update(double functionTime);

    void addPatternToQueue(int p);
    void iniLastPattern();
    void nextPattern();
    void goToNextPhase();

    void erase();

    std::vector<Pattern*>* getPatternQueue() { return &m_patternQueue;}

    //public attributes
    bool m_incontrol;
    Video *video;
    Online* online;
    GTexture* gtext;



    private:
    std::string m_name;

    std::vector<Pattern*> m_patternQueue;
    Pattern* m_pattern;

    std::vector<Object*>* m_objects;
    Object* m_lava;
    std::vector<Object*> m_walls;



    double m_fogdistancestart;
    double m_fogdistanceend;
    float m_fogr;
    float m_fogg;
    float m_fogb;

    double m_lavaspeed;

    double highestZ;
};


#endif // PHASE_H_INCLUDED
