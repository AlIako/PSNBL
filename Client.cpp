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


    (*params->addr)=target;

    (*params->clilen) = sizeof(*params->addr);

    if(params->tcp)
    {
        cerr<<"starting tcp connection thread"<<endl;
        *params->newsockfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket tcp
        //*params->newsockfd = socket (AF_INET, SOCK_STREAM, 0); //Create socket tcp
        //*params->newsockfd = socket(AF_INET, SOCK_DGRAM, 0); //Create socket udp

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

            //receive answer from server
            infosSocket infosRecu;
            int n = receiveSocket(params->tcp,*params->newsockfd, (char*)&infosRecu,sizeof(infosRecu), 0,(struct sockaddr *) (params->addr), (params->clilen));

            if (n < 0)
                cerr<<"ERROR receiving conn socket: "<<WSAGetLastError()<<endl;

            if(infosRecu.type==5)//serv response
                *(params->connectionEstablished)=true;

            (*params->clientID)=infosRecu.variable[0];

            cerr<<"server responded. my client id is "<< (int)infosRecu.variable[0]<<endl;

            (*params->socketsReceived).push_back(infosRecu);

            SDL_Delay(50);


            *(params->connectionEstablished)=true;
            cerr << "Connection succesful!"<<endl;
        }


        delete tempIp;

    }
    else
    {
        cerr<<"starting udp connection thread"<<endl;
        infosSocket infosRecu;
        infosRecu.type=4;//client connect
        cerr << "connecting..."<<endl;

        *params->newsockfd  = socket(AF_INET, SOCK_DGRAM, 0); //Create socket udp

        //send connection request to serv
        int n = sendSocket(params->tcp,*params->newsockfd,(char*)&infosRecu, sizeof(infosRecu),0,(struct sockaddr *) (params->addr), (*params->clilen));
        if (n < 0)
            cerr<<"ERROR writing from conn socket: "<<WSAGetLastError()<<endl;

        //receive answer from serv
        while(*(params->connectionEstablished)==false)
        {
            n = receiveSocket(params->tcp,*params->newsockfd, (char*)&infosRecu,sizeof(infosRecu), 0,(struct sockaddr *) (params->addr), (params->clilen));

            if (n < 0)
                cerr<<"ERROR reading to conn socket: "<<WSAGetLastError()<<endl;

            if(infosRecu.type==5)//serv response
                *(params->connectionEstablished)=true;
            SDL_Delay(50);
        }


        cerr << "Connection succesful!"<<endl;
    }


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
        infosSocket infosRecu;
        int n = receiveSocket(params->tcp,*params->newsockfd, (char*)&infosRecu,sizeof(infosRecu), 0,(struct sockaddr *) (params->addr), (params->clilen));
        if (n < 0)
            cerr<<"ERROR reading from socket: "<<WSAGetLastError()<<endl;

        //add received socket to queue
        if(infosRecu.type!=-1)
        {
            (*params->socketsReceived).push_back(infosRecu);
        }

        SDL_Delay(CLIENT_WAIT_RECEIVE);
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


            //infosSocket s=infosS;
            //cerr<<" sending socket type "<<(int)s.type << ", 0: "<< s.variable[0]  << ", 1: "<< s.variable[1] << ", 2: "<< s.variable[2] << ", 3: "<< s.variable[3] <<endl;

            //send
            int n = sendSocket(params->tcp,*params->newsockfd,(char*)&infosS, sizeof(infosS),0,(struct sockaddr *) (params->addr), (*params->clilen));
            //check any error
            if (n < 0)
                cerr<<"ERROR writing to socket: "<<WSAGetLastError()<<endl;

            //update queue
            for(unsigned int i=0;i<(*params->socketsToSend).size()-1;i++)
                (*params->socketsToSend)[i]=(*params->socketsToSend)[i+1];
            if((*params->socketsToSend).size()>0)
                (*params->socketsToSend).pop_back();
        }

        SDL_Delay(CLIENT_WAIT_SEND);
    }


    close(*params->newsockfd);
    cerr << "End client send thread"<<endl;
    return NULL;
}



