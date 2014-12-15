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

/*
    char buffer[80];
    memset(buffer, 0, sizeof(buffer)); //Clear the buffer
    params->n = recv (*params->newsockfd, buffer, sizeof(buffer)-1, 0);
    //params->n = read(*(params->newsockfd),params->buffer,255);
    if (params->n < 0)
        cerr<<"ERROR reading from socket: "<<WSAGetLastError()<<endl;
    cerr<<"(client)message received: "<<params->buffer<<endl;
*/

    //connect to server
    /*while(params!=NULL && *(params->connectionEstablished)==false)
    {

    }*/

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
        //recvfrom(params->sock,(char*)&infosRecu,sizeof(infosRecu),0,(SOCKADDR*)params->sin,&params->crecsize);
        params->n = recv (*params->newsockfd, (char*)&infosRecu,sizeof(infosRecu), 0);
        //params->n = read(*(params->newsockfd),params->buffer,255);
        if (params->n < 0)
            cerr<<"ERROR reading from socket: "<<WSAGetLastError()<<endl;


        //handle socket received
        if(infosRecu.type==1)//position from player
        {
            (*params->playerList)[1]->setPos(infosRecu.variable[0],infosRecu.variable[1]);
            (*params->playerList)[1]->setAngle(infosRecu.variable[2]);
        }
        SDL_Delay(WAIT_RECEIVE);
    }
    cerr << "End client receive thread"<<endl;
    return NULL;
}

void* clientSendThread(void* data)
{
    thread_params* params;
    params=(thread_params*)data;

    string tempString="hello yourself!";

    infosSocket infosS;

    while(params!=NULL && *(params->threadOn))
    {
        //position values
        infosS.type=1;
        infosS.variable[0]=(*params->playerList)[0]->getX();
        infosS.variable[1]=(*params->playerList)[0]->getY();
        infosS.variable[2]=(*params->playerList)[0]->getAngle();

        //send socket
        //params->n = send(*params->newsockfd, "hehehe",6, 0);
        //params->n = write(*(params->newsockfd),"hehehe",6);
        params->n = sendto(*params->newsockfd,(char*)&infosS, sizeof(infosS),0,(struct sockaddr *) &(params->cli_addr), (params->clilen));

        if (params->n < 0)
            cerr<<"ERROR writing to socket: "<<WSAGetLastError()<<endl;



        SDL_Delay(WAIT_SEND);
    }


    close(*params->newsockfd);
    cerr << "End client send thread"<<endl;
    return NULL;
}



