#include "Client.h"

void* clientConnectThread(void* data)
{
    thread_params* params;
    params=(thread_params*)data;

    //Start up Winsock…
    WSADATA wsadata;

    int error = WSAStartup(0x0202, &wsadata);

    //Did something happen?
    if (error)
        return false;

    //Did we get the right Winsock version?
    if (wsadata.wVersion != 0x0202)
    {
        WSACleanup(); //Clean up Winsock
        return false;
    }

    //Fill out the information needed to initialize a socket…
    SOCKADDR_IN target; //Socket address information

    target.sin_family = AF_INET; //address family Internet
    target.sin_port = htons (params->port); //Port to connect on

    char* tempIp=stringtochar(params->ip);
    target.sin_addr.s_addr = inet_addr (tempIp); //Target IP


    //*params->newsockfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
    *params->newsockfd = socket (AF_INET, SOCK_STREAM, 0); //Create socket

    if (*params->newsockfd <0)
    {
        cerr << "Couldn't create the socket"<<endl;
        return false; //Couldn't create the socket
    }


    //Try connecting...
    cerr << "Try connecting to " << tempIp << "("<<params->port<< ")..."<< endl;
    if (connect(*params->newsockfd, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
    {
        cerr << "Couldn't connect."<<endl;
    }
    else
    {
        *(params->connectionEstablished)=true;
        cerr << "Connection succesful!"<<endl;
    }


    delete tempIp;
    cerr << "End client connection thread"<<endl;
    return NULL;
}


void* clientReceiveThread(void* data)
{
    thread_params* params;
    params=(thread_params*)data;

    //receive informations from server
    while(params!=NULL && *(params->threadOn))
    {
        char buffer[80];
        memset(buffer, 0, sizeof(buffer)); //Clear the buffer

        infosSocket infosRecu;
        params->n = recv (*params->newsockfd, (char*)&infosRecu,sizeof(infosRecu), 0);
        if (params->n < 0)
            cerr<<"ERROR reading from socket: "<<WSAGetLastError()<<endl;

        //add received socket to queue
        if(infosRecu.type!=-1)
        {
            (*params->socketsReceived).push_back(infosRecu);
        }

        SDL_Delay(WAIT_RECEIVE);
    }
    cerr << "End client receive thread"<<endl;
    return NULL;
}

void* clientSendThread(void* data)
{
    thread_params* params=(thread_params*)data;

    infosSocket infosS;

    while(params!=NULL && *(params->threadOn))
    {
        //if there is something to send
        if((*params->socketsToSend).size()>0)
        {
            //take first element of queue
            infosS=(*params->socketsToSend)[0];
            //send
            params->n = sendto(*params->newsockfd,(char*)&infosS, sizeof(infosS),0,(struct sockaddr *) &(params->cli_addr), (params->clilen));
            //check any error
            if (params->n < 0)
                cerr<<"ERROR writing to socket: "<<WSAGetLastError()<<endl;
            //update queue
            for(unsigned int i=0;i<(*params->socketsToSend).size()-1;i++)
                (*params->socketsToSend)[0]=(*params->socketsToSend)[1];
            if((*params->socketsToSend).size()>0)
                (*params->socketsToSend).pop_back();
        }

        SDL_Delay(WAIT_SEND);
    }


    close(*params->newsockfd);
    cerr << "End client send thread"<<endl;
    return NULL;
}



