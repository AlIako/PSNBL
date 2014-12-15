#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#include <pthread.h>
#include "threadStructures.h"


void* handleConnections(void* data);
void* serverReceiveThread(void* data);
void* serverSendThread(void* data);

#endif // SERVER_H_INCLUDED
