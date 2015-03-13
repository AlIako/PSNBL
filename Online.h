#ifndef ONLINE_H_INCLUDED
#define ONLINE_H_INCLUDED
#include "Config.h"
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
    void startThreads();

    void update();

    void sendSocket(infosSocket s);
    void sendSocketReplace(infosSocket s);

    int nextConfirmationID();

    infosSocket getNextSocket();
    infosSocket getNextSocketRemove();

    void setIncontrol(bool b) { m_incontrol=b;}
    bool inControl() {return m_incontrol;}

    void setActive(bool a){m_active=a;}
    bool active() {return m_active;}

    std::string getOnlineName() {return m_onlineName; }

    void closeOnline();
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

    std::vector<infosClient> clients;
    std::vector<SocketWrapper> socketWrappersToSend;

    int* newsockfd;

    int m_port;
    string m_ip;

    bool m_tcp;//if false -> udp

    int nextConfirmID;//ID for socket confirmation. Append each time to keep it unique
    std::vector<cID> confirmIDreceived;//IDs that were received, so that you dont receive and handle a same socket twice

    std::string m_onlineName;

    bool m_serverOn;
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
