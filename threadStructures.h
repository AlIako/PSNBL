#ifndef THREADSTRUCTURES_H_INCLUDED
#define THREADSTRUCTURES_H_INCLUDED

#if defined (WIN32)
#include <winsock2.h>
#elif defined (linux)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close (s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
#endif
#include <unistd.h>
#include <iostream>
#include "utilFunctions.h"
#include <vector>
#include "GTime.h"

#define TEXT_SIZE 50

#define SERV_WAIT_SEND 10
#define SERV_WAIT_RECEIVE 10

#define CLIENT_WAIT_SEND 60
#define CLIENT_WAIT_RECEIVE 10

#include <semaphore.h>

using namespace std;


int sendSocket(bool tcp,SOCKET s,const char* infosS,int sizeInfosS,int wut,const struct sockaddr* paramsin,int crecsize);
int receiveSocket(bool tcp,SOCKET s,char* infosS,int sizeInfosS,int wut,struct sockaddr* paramsin=NULL,int* crecsize=NULL);




struct infosSocket
{
    char type;
    float variable[10];
    char text[TEXT_SIZE];
};

struct infosClient
{
    sockaddr_in *addr;
    int clilen;
    int *sock;
    int id;
    GTime lastHeardFrom;
};

struct thread_params
{
    bool* threadOn;
    bool* connectionEstablished;
    int port;
    string ip;

    sem_t *mutex;

    bool tcp;

    std::vector<infosSocket>* socketsReceived;
    std::vector<infosSocket>* socketsToSend;
    std::vector<infosClient>* clients;

    int *clientID;

    int *newsockfd, *clilen;
    sockaddr_in *addr;
};

#endif // THREADSTRUCTURES_H_INCLUDED
