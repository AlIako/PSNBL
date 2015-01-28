#include "Online.h"

Online* Online::m_instance = new Online();


Online* Online::getInstance()
{
    return m_instance;
}


Online::Online()
{
    m_incontrol=true;
    m_active=true;

    m_server=false;
    m_connectionEstablished=false;

    m_tcp=false;

    clientID=0;
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

            socketsToSend.push_back(s);
            //if(s.type==8)
            //cerr<<socketsToSend.size()<<" sending socket type "<<(int)s.type << ": "<< s.variable[0]  << ", 1: "<< s.variable[1] << ", 2: "<< s.variable[2] << ", 3: "<< s.variable[3] <<endl;
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
        for(unsigned int i=0;i<socketsToSend.size();i++)
        {
            if((int)socketsToSend[i].variable[0]==cl && socketsToSend[i].type==s.type)
            {
                socketFound=true;
                socketsToSend[i]=s;
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
    if(socketsReceived.size()<=0)
        return s;

    return socketsReceived[0];
}

//get next socket from the list and remove it
infosSocket Online::getNextSocketRemove()
{
    infosSocket s=getNextSocket();

    for(int i=0;i<(int)socketsReceived.size()-1;i++)
        socketsReceived[i]=socketsReceived[i+1];
    if(socketsReceived.size()>0)
        socketsReceived.pop_back();


    return s;
}

void Online::ini()
{
    //read settings file
    readMultiplayerFile();

    if(m_active)
    {
        paramsHandleConnectionsThread.threadOn=&m_threadsOn;
        paramsHandleConnectionsThread.connectionEstablished=&m_connectionEstablished;
        paramsHandleConnectionsThread.socketsReceived=&socketsReceived;
        paramsHandleConnectionsThread.socketsToSend=&socketsToSend;
        paramsHandleConnectionsThread.clients=&clients;
        paramsHandleConnectionsThread.port=m_port;
        paramsHandleConnectionsThread.ip=m_ip;
        paramsHandleConnectionsThread.tcp=m_tcp;
        paramsHandleConnectionsThread.newsockfd=new int;
        paramsHandleConnectionsThread.addr=new sockaddr_in;
        paramsHandleConnectionsThread.clilen=new int;
        paramsHandleConnectionsThread.clientID=&clientID;
        paramsHandleConnectionsThread.mutex=&mutex;

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
    ifstream file("config.ini", ios::in);

    if(file)
    {
        std::string befor_read="",read_name="",read_name_before="";
        std::string cur_read="";
        int cur_int=0;

        while(!file.eof())
        {
            read_name=cur_read.substr(0,cur_read.size()-1);//enleve le ":"

            if(read_name=="name")
            {
                file >> cur_read;
                cerr<<"name: "<<cur_read<<endl;
            }
            else if(read_name=="ip")
            {
                file >> cur_read;
                m_ip=cur_read;
                cerr<<"ip: "<<cur_read<<endl;
            }
            else if(read_name_before=="port")
            {
                file >> cur_int;
                m_port=cur_int;
                cerr<<"port: "<<cur_int<<endl;
            }
            else if(read_name=="mode")
            {
                file >> cur_read;
                cerr<<"mode: "<<cur_read<<endl;

                if(cur_read.find("server")!=string::npos)
                    m_server=true;
                else m_server=false;
            }
            else if(read_name=="protocol")
            {
                file >> cur_read;
                cerr<<"protocol: "<<cur_read<<endl;

                if(cur_read.find("tcp")!=string::npos)
                    m_tcp=true;
                else m_tcp=false;
            }

            file >> cur_read;
            befor_read=cur_read;
            read_name_before=befor_read.substr(0,befor_read.size()-1);//enleve le ":"

        }

        cerr<<endl;
        file.close();
    }
    else
        cerr << "can't open file (multiplayer settings)" << endl;

}

void Online::close()
{
    //close threads
    m_connectionEstablished=false;
    m_threadsOn=false;
}



Online::~Online()
{

}

