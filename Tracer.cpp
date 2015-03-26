#include "Tracer.h"


Trace::Trace(string m)
{
    channel="";
    msg=m;
    sent=false;
    id=-1;
}

Tracer* Tracer::m_instance = new Tracer();


Tracer* Tracer::getInstance()
{
    return m_instance;
}



Tracer::Tracer()
{
    m_enabled=false;
    //m_channels.push_back("rope");
    //m_channels.push_back("crosshair");
    //m_channels.push_back("jumpblock");
    //m_channels.push_back("spell");
    //m_channels.push_back("jump");
    m_channels.push_back("video");
    m_channels.push_back("fireball");
    m_channels.push_back("damage");
    m_channels.push_back("phase");
    m_channels.push_back("fade");
    m_channels.push_back("warning");
    m_channels.push_back("light");
    //m_channels.push_back("boss");
    //m_channels.push_back("debug");

    m_channelsSize=m_channels.size();
}



void Tracer::trace(string channel, string output, int timeLapse, int id)
{
    if(m_enabled)
    {
        bool authorizeNewTrace=false;
        Trace* toSend=new Trace(output);
        toSend->channel=channel;
        toSend->id=id;
        toSend->sent=false;

        if(channelOn(channel))
        {
            if(id!=-1)//for renewal each x seconds
            {
                Trace* sentTrace=getTrace(id,channel);
                if(sentTrace!=NULL)//already sent
                {
                    sentTrace->timeSent.couler();
                    if(sentTrace->timeSent.ecouler(timeLapse))
                    {
                        sentTrace->msg=output;
                        sentTrace->sent=false;
                        sentTrace->timeSent.reset();
                    }
                }
                else
                    authorizeNewTrace=true;
            }
            else
                authorizeNewTrace=true;
        }

        if(authorizeNewTrace)
            m_traces.push_back(toSend);
    }
}
void Tracer::traceCerr(string channel, string output, int timeLapse, int id)
{
    if(m_enabled)
    {
        if(channelOn(channel))
        {
            cerr<<"tracer ("<<channel<<"):"<<output<<endl;
        }
    }
}

void Tracer::afterFetch()
{
    for(unsigned int i=0;i<m_traces.size();i++)
        if(m_traces[i]->id==-1)
        {
            delete m_traces[i];
            m_traces.erase(m_traces.begin()+i);
        }
}


Trace* Tracer::getTrace(int id, string ch)
{
    for(unsigned int i=0;i<m_traces.size();i++)
        if(m_traces[i]->id==id && (ch=="" || ch==m_traces[i]->channel))
            return m_traces[i];
    return NULL;
}

void Tracer::addChannel(string ch)
{
    m_channels.push_back(ch);
    m_channelsSize+=1;
}

void Tracer::reset()
{
    m_channels.clear();
    m_channelsSize=0;
    m_traces.clear();
}
void Tracer::clearChannels()
{
    m_channels.clear();
    m_channelsSize=0;
}



bool Tracer::channelOn(string channel)
{
    for(unsigned int i=0;i<m_channelsSize;i++)
    {
        if(channel==m_channels[i])
            return true;
    }
    return false;
}






