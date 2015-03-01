#ifndef TRACER_H_INCLUDED
#define TRACER_H_INCLUDED
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "GTime.h"

using namespace std;

class Trace
{
public:
    Trace(string m);
    string msg;
    string channel;
    bool sent;
    GTime timeSent;
    int id;
};

class Tracer
{
    public:
    static Tracer* getInstance();

    void enable(){m_enabled=true;}
    void disable(){m_enabled=false;}


    void trace(string channel, string output, int timeLapse=0, int id=-1);
    void afterFetch();

    void addChannel(string ch);
    void reset();
    void clearChannels();

    bool channelOn(string channel);
    Trace* getTrace(int id, string ch="");

    vector<Trace*>* getTraces(){return &m_traces;}

    private:
    Tracer();
    static Tracer* m_instance;

    vector<string> m_channels;
    unsigned int m_channelsSize;
    vector<Trace*> m_traces;

    bool m_enabled;
};

#endif // TRACER_H_INCLUDED
