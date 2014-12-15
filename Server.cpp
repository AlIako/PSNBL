#include "Server.h"

void* handleConnections(void* data)
{
    thread_params* params;
    params=(thread_params*)data;

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

        s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); // Create socket
        //s = socket (AF_INET, SOCK_STREAM, 0); // Create socket

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


        //params->cli_addr=addr;

        //socklen_t size = sizeof(client_addr);

        params->clilen = sizeof(params->cli_addr);
        *params->newsockfd = accept(s, (struct sockaddr *) &(params->cli_addr), &(params->clilen));
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
    //}
    cerr << "End handle connections thread"<<endl;
    return NULL;
}

void* serverReceiveThread(void* data)
{
    thread_params* params;
    params=(thread_params*)data;

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
    cerr << "End server receive thread"<<endl;
    return NULL;
}

void* serverSendThread(void* data)
{
    thread_params* params;
    params=(thread_params*)data;

    string tempString="hello :)";

    infosSocket infosS;
   /* infosS.type=0;
    for(int j=0;j<15;j++)
    {
        if(j>=(int)tempString.size())
            infosS.text[j]='\0';
        else
            infosS.text[j]=tempString[j];
    }
    infosS.text[15]='\0';*/


    //infinite while
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
    cerr << "End server send thread"<<endl;
    return NULL;
}
