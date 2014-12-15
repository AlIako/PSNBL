#include "Online.h"



Online::Online()
{
    m_server=false;
    m_connectionEstablished=false;
}



void Online::ini()
{
    //read settings file
    readMultiplayerFile();

    if(true)
    {
        paramsHandleConnectionsThread.threadOn=&m_threadsOn;
        paramsHandleConnectionsThread.connectionEstablished=&m_connectionEstablished;
        paramsHandleConnectionsThread.playerList=playerList;
        paramsHandleConnectionsThread.port=m_port;
        paramsHandleConnectionsThread.ip=m_ip;
        paramsHandleConnectionsThread.newsockfd=new int;

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
    if(true)
    {
        //client
        if(m_server==false)
        {
            //check if client finally established connection to server, then launch receive and send threads
            if(m_threadsOn==false && m_connectionEstablished)
            {
                cerr<<"Connection to server established! launching threads..."<<endl;

                //receive thread
                paramsHandleClientReceiveThread=paramsHandleConnectionsThread;
                pthread_create(&clientReceivePThread,NULL, clientReceiveThread,&paramsHandleClientReceiveThread);
                //send thread
                paramsHandleClientSendThread=paramsHandleConnectionsThread;
                pthread_create(&clientSendPThread,NULL, clientSendThread,&paramsHandleClientSendThread);

                m_threadsOn=true;
            }
        }
        else
        {
            //check if client finally established connection to server, then launch receive and send threads
            if(m_threadsOn==false && m_connectionEstablished)
            {
                cerr<<"Connection to server established! launching threads..."<<endl;

                //receive thread
                paramsServerReceiveThread=paramsHandleConnectionsThread;
                pthread_create(&serverReceivePThread,NULL, serverReceiveThread,&paramsServerReceiveThread);
                //send thread
                paramsServerSendThread=paramsHandleConnectionsThread;
                pthread_create(&serverSendPThread,NULL, serverSendThread,&paramsServerSendThread);

                m_threadsOn=true;
            }
        }
    }
}


void Online::readMultiplayerFile()
{
    ifstream file("data/multiplayer.txt", ios::in);

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

