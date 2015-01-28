#ifndef ONLINE_H_INCLUDED
#define ONLINE_H_INCLUDED
#include <fstream>
#include <iostream>
#include "Client.h"
#include "Server.h"
#define RECEIVE_SOCKET_HANDLE_PER_FRAME 10

using namespace std;

class Online
{
    public:
    static Online* getInstance();

    void ini();
    void readMultiplayerFile();

    void update();

    void sendSocket(infosSocket s);
    void sendSocketReplace(infosSocket s);

    infosSocket getNextSocket();
    infosSocket getNextSocketRemove();

    void setIncontrol(bool b) { m_incontrol=b;}
    bool inControl() {return m_incontrol;}
    bool active() {return m_active;}

    void close();
    ~Online();

    std::vector<infosSocket> socketsReceived;
    int clientID;
    bool m_connectionEstablished;
    bool m_server;//false for client

    private:
    Online();
    static Online* m_instance;


    bool m_incontrol;
    bool m_active;

    std::vector<infosSocket> socketsToSend;
    std::vector<infosClient> clients;

    SOCKET newsockfd;

    int m_port;
    string m_ip;

    bool m_tcp;//if false -> udp



    bool m_threadsOn;

    //threads serv
    pthread_t handleConnectionsPThread;
    thread_params paramsHandleConnectionsThread;

    pthread_t serverReceivePThread;
    thread_params paramsServerReceiveThread;
    pthread_t serverSendPThread;
    thread_params paramsServerSendThread;

    //threads client
    pthread_t clientConnectThreadPThread;
    thread_params paramsClientConnectThreadThread;

    pthread_t clientReceivePThread;
    thread_params paramsHandleClientReceiveThread;
    pthread_t clientSendPThread;
    thread_params paramsHandleClientSendThread;

    //mutex
    sem_t mutex;

};

#endif // ONLINE_H_INCLUDED
