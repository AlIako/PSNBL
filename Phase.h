#ifndef PHASE_H_INCLUDED
#define PHASE_H_INCLUDED
#include "Online.h"
#include "Pattern.h"

class Phase
{
    public:
    Phase();

    void ini(std::vector<Object*>* objects);
    void iniMap();
    void iniPhaseProperties();

    void update(double functionTime);

    void addPatternToQueue(string name, double startz=-1);
    void iniLastPattern();
    void nextPattern();
    void goToNextPhase();

    void sendPatternOnline(int sendTo=-1);

    void setName(string name){m_name=name;}

    void erase();

    std::vector<Pattern*>* getPatternQueue() { return &m_patternQueue;}

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
    double nextZ;
};


#endif // PHASE_H_INCLUDED
