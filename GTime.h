#ifndef GTEMPS_H_INCLUDED
#define GTEMPS_H_INCLUDED
#include <SDL/SDL.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class GTime
{
    public:
    GTime();
    void reset();
    void couler();
    void stopper();
    void relancer();
    void rapport(string t);
    bool ecouler(int v);
    std::string getType();
    int timePast();
    void setTimePast(int t);

    private:
    bool m_stop;
    bool temps_coule;
    std::string m_type;
    int m_tempsActuel;
    int m_tempsPrecedent;

};


#endif // GTEMPS_H_INCLUDED
