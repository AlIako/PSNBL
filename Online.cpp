#include "Online.h"


Online* Online::m_instance = new Online();


Online* Online::getInstance()
{
    return m_instance;
}


Online::Online()
{
    m_active=true;
}

//add socket to send to the list
void Online::sendSocket(infosSocket s)
{
    if(m_active)
    {
        if(m_connectionEstablished)
        {
            int cl=clientID;
            if(m_server) cl=0;
            s.variable[0]=cl;


            SocketWrapper sw;
            sw.socket=s;
            //if(s.type==8)
            //cerr<<socketsToSend.size()<<" sending socket type "<<(int)s.type << ": "<< s.variable[0]  << ", 1: "<< s.variable[1] << ", 2: "<< s.variable[2] << ", 3: "<< s.variable[3] <<endl;


            //if server, push back socket for EACH client to SocketWrapper list
            if(m_server)
            {
                for(unsigned int i=0;i<clients.size();i++)
                {
                    sw.client=clients[i];
                    socketWrappersToSend.push_back(sw);
                }
            }
            else//client, just add it once (just send it to server)
            {
                socketWrappersToSend.push_back(sw);
            }
        }
    }
}


//if socket already in list, just replace it
void Online::sendSocketReplace(infosSocket s)
{
    if(m_active)
    {
        int cl=clientID;
        if(m_server) cl=0;
        s.variable[0]=cl;

        //cerr<<socketsToSend.size()<<" sending socketR type "<<(int)s.type << ", 0: "<< s.variable[0]  << ", 1: "<< s.variable[1] << ", 2: "<< s.variable[2] << ", 3: "<< s.variable[3] <<endl;
        //check if already in list
        bool socketFound=false;
        for(unsigned int i=0;i<socketWrappersToSend.size();i++)
        {
            if((int)socketWrappersToSend[i].socket.variable[0]==cl && socketWrappersToSend[i].socket.type==s.type)
            {
                socketFound=true;
                socketWrappersToSend[i].socket=s;
            }
        }
        //cerr<<socketsToSend.size()<<" sending socketR type "<<(int)s.type << ": "<< s.variable[0]  << ", 1: "<< s.variable[1] << ", 2: "<< s.variable[2] << ", 3: "<< s.variable[3] <<endl;


        //if not in list, add to list
        if(!socketFound)
            sendSocket(s);
    }
}

//get next socket from the list
infosSocket Online::getNextSocket()
{
    infosSocket s;
    s.type=-1;
    s.confirmationID=-1;
    if(socketsReceived.size()<=0)
        return s;

    return socketsReceived[0];
}

//get next socket from the list and remove it
infosSocket Online::getNextSocketRemove()
{
    infosSocket s=getNextSocket();

    if(socketsReceived.size()>0)
        socketsReceived.erase(socketsReceived.begin());

    return s;
}

void Online::ini()
{
    m_incontrol=true;

    m_server=false;
    m_connectionEstablished=false;

    m_tcp=false;

    clientID=0;

    nextConfirmID=50;

    m_serverOn=true;

    newsockfd=new int;

    //read settings file
    readMultiplayerFile();
}
void Online::startThreads()
{
    if(m_active)
    {
        paramsHandleConnectionsThread.threadOn=&m_threadsOn;
        paramsHandleConnectionsThread.serverOn=&m_serverOn;
        paramsHandleConnectionsThread.connectionEstablished=&m_connectionEstablished;
        paramsHandleConnectionsThread.socketsReceived=&socketsReceived;
        paramsHandleConnectionsThread.clients=&clients;
        paramsHandleConnectionsThread.socketWrappersToSend=&socketWrappersToSend;
        paramsHandleConnectionsThread.confirmIDreceived=&confirmIDreceived;
        paramsHandleConnectionsThread.port=m_port;
        paramsHandleConnectionsThread.ip=m_ip;
        paramsHandleConnectionsThread.tcp=m_tcp;
        paramsHandleConnectionsThread.newsockfd=newsockfd;
        paramsHandleConnectionsThread.addr=new sockaddr_in;
        paramsHandleConnectionsThread.clilen=new int;
        paramsHandleConnectionsThread.clientID=&clientID;
        paramsHandleConnectionsThread.mutex=&mutex;
        paramsHandleConnectionsThread.modifArray=new bool(false);

        sem_init(&mutex, 0, 1);

        //serv threads
        if(m_server)
        {
            m_connectionEstablished=false;
            //connections thread
            pthread_create(&handleConnectionsPThread,NULL, handleConnections,&paramsHandleConnectionsThread);

        }
        else//client thread
        {
            m_connectionEstablished=false;
            //connection thread
            paramsClientConnectThreadThread=paramsHandleConnectionsThread;
            pthread_create(&clientConnectThreadPThread,NULL, clientConnectThread,&paramsClientConnectThreadThread);
        }
    }
}

void Online::update()
{
    if(m_active)
    {
        //client
        if(m_server==false)
        {
            //check if client finally established connection to server, then launch receive and send threads
            if(m_threadsOn==false && m_connectionEstablished)
            {
                cerr<<"Connection to server established! launching threads..."<<endl;
                m_threadsOn=true;

                //receive thread
                paramsHandleClientReceiveThread=paramsHandleConnectionsThread;
                pthread_create(&clientReceivePThread,NULL, clientReceiveThread,&paramsHandleClientReceiveThread);
                //send thread
                paramsHandleClientSendThread=paramsHandleConnectionsThread;
                pthread_create(&clientSendPThread,NULL, clientSendThread,&paramsHandleClientSendThread);

            }
        }
        else
        {
            //check if client finally established connection to server, then launch receive and send threads
            if(m_threadsOn==false && m_connectionEstablished)
            {
                cerr<<"Connection to a client established! launching threads..."<<endl;
                m_threadsOn=true;

                //receive thread
                paramsServerReceiveThread=paramsHandleConnectionsThread;
                pthread_create(&serverReceivePThread,NULL, serverReceiveThread,&paramsServerReceiveThread);
                //send thread
                paramsServerSendThread=paramsHandleConnectionsThread;
                pthread_create(&serverSendPThread,NULL, serverSendThread,&paramsServerSendThread);

            }
        }
    }
}


void Online::readMultiplayerFile()
{

    m_onlineName=Config::getInstance()->name;
    m_ip=Config::getInstance()->ip;
    m_port=Config::getInstance()->port;

    if(Config::getInstance()->mode.find("server")!=string::npos)
        m_server=true;
    else m_server=false;

    if(Config::getInstance()->mode.find("tcp")!=string::npos)
        m_tcp=true;
    else m_tcp=false;
}

int Online::nextConfirmationID()
{
    nextConfirmID++;
    return nextConfirmID;
}


void Online::closeOnline()
{
    //close threads
    m_connectionEstablished=false;
    m_threadsOn=false;
    m_serverOn=false;


    sem_post(&mutex);
    if(m_server)
    {
        pthread_cancel(handleConnectionsPThread);
        pthread_cancel(serverReceivePThread);
    }
    else
    {
        pthread_cancel(clientReceivePThread);
    }

    clients.clear();
    socketWrappersToSend.clear();
    confirmIDreceived.clear();
    socketsReceived.clear();
    clientID=0;
    nextConfirmID=50;

    cerr<<"Online service closed."<<endl;
}



Online::~Online()
{

}

