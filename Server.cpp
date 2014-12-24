#include "Server.h"

void* handleConnections(void* data)
{
    cerr << "Begin handle connections thread"<<endl;
    thread_params* params=(thread_params*)data;

    WSADATA w;

    /*while(params!=NULL && *(params->connectionEstablished)==false)
    {*/
        int error = WSAStartup (0x0202, &w);   // Fill in WSA info

        if (error)
        {
            return false; //For some reason we couldn't start Winsock
        }

        if (w.wVersion != 0x0202) //Wrong Winsock version?
        {
            WSACleanup ();
            return false;
        }
        SOCKET s;
        SOCKADDR_IN addr; // The address structure for a TCP socket

        addr.sin_family = AF_INET;      // Address family
        addr.sin_port = htons (params->port);   // Assign port to this socket

        //Accept a connection from any IP using INADDR_ANY
        //You could pass inet_addr("0.0.0.0") instead to accomplish the
        //same thing. If you want only to watch for a connection from a
        //specific IP, specify that //instead.
        addr.sin_addr.s_addr = htonl (INADDR_ANY);


    params->addr=addr;
    params->clilen = sizeof(params->addr);

    if(params->tcp)
    {
        s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); // Create socket tcp
        //s = socket (AF_INET, SOCK_STREAM, 0); // Create socket tcp

        if (s == INVALID_SOCKET)
        {
            cerr << "Couldn't create the socket"<<endl;
            return false; //Don't continue if we couldn't create a //socket!!
        }

        if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
        {
            cerr << "Couldn't bind"<<endl;
           //We couldn't bind (this will happen if you try to bind to the same
           //socket more than once)
            return false;
        }

        //Now we can start listening (allowing as many connections as possible to
        //be made at the same time using SOMAXCONN). You could specify any
        //integer value equal to or lesser than SOMAXCONN instead for custom
        //purposes). The function will not //return until a connection request is
        //made
        listen(s, SOMAXCONN);



        *params->newsockfd = accept(s, (struct sockaddr *) &(params->addr), &(params->clilen));
        if (*params->newsockfd < 0)
        {
            cerr<<"ERROR on accept: "<<WSAGetLastError()<<endl;
        }
        else
        {
            *(params->connectionEstablished)=true;
            cerr << "Client connected!"<<endl;
        }

        close(s);

        //Don't forget to clean up with CloseConnection()!

        SDL_Delay(10);
    }
    else//udp
    {
         *params->newsockfd  = socket(AF_INET, SOCK_DGRAM, 0); //Create socket udp
        bind(*params->newsockfd, (SOCKADDR*)&addr, (params->clilen));

        cerr<<"waiting for client..."<<endl;
        infosSocket infosRecu;
        //recvfrom(params->sock,(char*)&infosRecu,sizeof(infosRecu),0,(SOCKADDR*)params->sin,&params->crecsize);
        while(*(params->connectionEstablished)==false)
        {
            params->n = receiveSocket(params->tcp,*params->newsockfd, (char*)&infosRecu,sizeof(infosRecu), 0,(struct sockaddr *) &(params->addr), &(params->clilen));

            if (params->n < 0)
                cerr<<"ERROR reading from conn socket: "<<WSAGetLastError()<<endl;
            if(infosRecu.type==4)//client connect
                *(params->connectionEstablished)=true;
        }

        infosRecu.type=5;//serv response
        params->n = sendSocket(params->tcp,*params->newsockfd,(char*)&infosRecu, sizeof(infosRecu),0,(struct sockaddr *) &(params->addr), (params->clilen));
        if (params->n < 0)
            cerr<<"ERROR writing to conn socket: "<<WSAGetLastError()<<endl;


        cerr << "Connection succesful!"<<endl;
    }
    //}
    cerr << "End handle connections thread"<<endl;
    return NULL;
}

void* serverReceiveThread(void* data)
{
    cerr << "Begin server receive thread"<<endl;
    thread_params* params;
    params=(thread_params*)data;

    while(params!=NULL && *(params->threadOn))
    {
        char buffer[80];
        memset(buffer, 0, sizeof(buffer)); //Clear the buffer

        infosSocket infosRecu;
        //recvfrom(params->sock,(char*)&infosRecu,sizeof(infosRecu),0,(SOCKADDR*)params->sin,&params->crecsize);
        params->n = receiveSocket(params->tcp,*params->newsockfd, (char*)&infosRecu,sizeof(infosRecu), 0,(struct sockaddr *) &(params->addr), &(params->clilen));
        //params->n = read(*(params->newsockfd),params->buffer,255);
        if (params->n < 0)
            cerr<<"ERROR reading from socket: "<<WSAGetLastError()<<endl;

        //add received socket to queue
        if(infosRecu.type!=-1)
        {
            (*params->socketsReceived).push_back(infosRecu);
        }
        SDL_Delay(WAIT_RECEIVE);
    }
    cerr << "End server receive thread"<<endl;
    return NULL;
}

void* serverSendThread(void* data)
{
    cerr << "Begin server send thread"<<endl;
    thread_params* params;
    params=(thread_params*)data;

    string tempString="hello :)";

    infosSocket infosS;

    //infinite while
    while(params!=NULL && *(params->threadOn))
    {
        //if there is something to send
        if((*params->socketsToSend).size()>0)
        {
            //take first element of queue
            infosS=(*params->socketsToSend)[0];
            //send
            params->n = sendSocket(params->tcp,*params->newsockfd,(char*)&infosS, sizeof(infosS),0,(struct sockaddr *) &(params->addr), (params->clilen));
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
    cerr << "End server send thread"<<endl;
    return NULL;
}
