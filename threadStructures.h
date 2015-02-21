#ifndef THREADSTRUCTURES_H_INCLUDED
#define THREADSTRUCTURES_H_INCLUDED

#define SERV_WAIT_SEND 10
#define SERV_WAIT_RECEIVE 10

#define CLIENT_WAIT_SEND 60
#define CLIENT_WAIT_RECEIVE 10

#include "SocketWrapper.h"


using namespace std;


int sendSocket(bool tcp,SOCKET s,const char* infosS,int sizeInfosS,int wut,const struct sockaddr* paramsin,int crecsize);
int receiveSocket(bool tcp,SOCKET s,char* infosS,int sizeInfosS,int wut,struct sockaddr* paramsin=NULL,int* crecsize=NULL);





struct thread_params
{
    bool* threadOn;
    bool* connectionEstablished;
    int port;
    string ip;

    sem_t *mutex;

    bool tcp;

    std::vector<infosSocket>* socketsReceived;
    std::vector<infosClient>* clients;
    std::vector<SocketWrapper>* socketWrappersToSend;

    int *clientID;

    int *newsockfd, *clilen;
    sockaddr_in *addr;
};

#endif // THREADSTRUCTURES_H_INCLUDED
