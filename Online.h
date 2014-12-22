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
    Online();

    void ini();
    void readMultiplayerFile();

    void update();

    void sendSocket(infosSocket s);
    void sendSocketReplace(infosSocket s);

    infosSocket getNextSocket();
    infosSocket getNextSocketRemove();

    void close();
    ~Online();


    private:

    std::vector<infosSocket> socketsReceived;
    std::vector<infosSocket> socketsToSend;

    SOCKET newsockfd;

    int m_port;
    string m_ip;





    bool m_server;//false for client
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

    bool m_connectionEstablished;

};

#endif // ONLINE_H_INCLUDED
