#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
#include <pthread.h>
#include "threadStructures.h"


void* clientConnectThread(void* data);
void* clientReceiveThread(void* data);
void* clientSendThread(void* data);

#endif // CLIENT_H_INCLUDED
