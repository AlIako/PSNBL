#ifndef THREADSTRUCTURES_H_INCLUDED
#define THREADSTRUCTURES_H_INCLUDED


#include "SocketWrapper.h"


using namespace std;


int sendSocket(bool tcp,SOCKET s,const char* infosS,int sizeInfosS,int wut,const struct sockaddr* paramsin,int crecsize);
int receiveSocket(bool tcp,SOCKET s,char* infosS,int sizeInfosS,int wut,struct sockaddr* paramsin=NULL,int* crecsize=NULL, int timeoutValue=5);


struct cID
{
    int idConfirm;
    int idClient;
};


struct thread_params
{
    bool* threadOn;
    bool* serverOn;
    bool* connectionEstablished;
    int port;
    string ip;

    sem_t *mutex;

    bool tcp;

    bool* modifArray;

    std::vector<infosSocket>* socketsReceived;
    std::vector<infosClient>* clients;
    std::vector<SocketWrapper>* socketWrappersToSend;
    std::vector<cID>* confirmIDreceived;

    int *clientID;

    int *newsockfd, *clilen;
    sockaddr_in *addr;
};

#endif // THREADSTRUCTURES_H_INCLUDED
