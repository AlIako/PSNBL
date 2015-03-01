#include "Tracer.h"

Tracer* Tracer::m_instance = new Tracer();


Tracer* Tracer::getInstance()
{
    return m_instance;
}



Tracer::Tracer()
{
    m_enabled=false;
    m_channels.push_back("rope");

    m_channelsSize=m_channels.size();
}



void Tracer::trace(string channel, string output, int timeLapse, int id)
{
    bool authorizeNewTrace=false;
    Trace* toSend=new Trace(output);
    toSend->channel=channel;

    if(channelOn(channel))
    {
        if(id!=-1)//for renewal each x seconds
        {
            Trace* sentTrace=getTrace(id);
            if(sentTrace!=NULL)//already sent
            {
                sentTrace->timeSent.couler();
                if(sentTrace->timeSent.ecouler(timeLapse))
                {
                    sentTrace->timeSent.reset();
                    authorizeNewTrace=true;
                }
            }
            else//didnt send yet
                m_sent.push_back(toSend);
        }
        else
            authorizeNewTrace=true;
    }

    if(authorizeNewTrace)
        m_traces.push_back(toSend);
}


Trace* Tracer::getTrace(int id, string ch)
{
    for(unsigned int i=0;i<m_sent.size();i++)
        if(m_sent[i]->id==id && (ch=="" || ch==m_sent[i]->channel))
            return m_sent[i];
    return NULL;
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






