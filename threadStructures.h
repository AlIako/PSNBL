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

#define TEXT_SIZE 50
#define WAIT_SEND 60
#define WAIT_RECEIVE 60

using namespace std;


int sendSocket(bool tcp,SOCKET s,const char* infosS,int sizeInfosS,int wut,const struct sockaddr* paramsin,int crecsize);
int receiveSocket(bool tcp,SOCKET s,char* infosS,int sizeInfosS,int wut,struct sockaddr* paramsin=NULL,int* crecsize=NULL);




struct infosSocket
{
    char type;
    float variable[10];
    char text[TEXT_SIZE];
};

struct client
{
    sockaddr_in *addr;
};

struct thread_params
{
    bool* threadOn;
    bool* connectionEstablished;
    int port;
    string ip;

    bool tcp;

    std::vector<infosSocket>* socketsReceived;
    std::vector<infosSocket>* socketsToSend;

    int *newsockfd, *clilen;
    sockaddr_in *addr;
};

#endif // THREADSTRUCTURES_H_INCLUDED
