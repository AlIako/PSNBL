#ifndef SOCKETWRAPPER_H_INCLUDED
#define SOCKETWRAPPER_H_INCLUDED

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

#include <semaphore.h>


#include "GTime.h"
#define TEXT_SIZE 50

struct infosSocket
{
    char type;
    float variable[10];
    char text[TEXT_SIZE];

    int confirmationID;//-1 if no confirmation needed.
};


struct infosClient
{
    sockaddr_in *addr;
    int clilen;
    int *sock;
    int id;
    GTime lastHeardFrom;
};


class SocketWrapper
{
    public:
    SocketWrapper();

    infosSocket socket;
    infosClient client;
    GTime untilSend;
    int timeTilResend;

    private:

};

#endif // SOCKETWRAPPER_H_INCLUDED
