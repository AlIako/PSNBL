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
    SOCKADDR_IN addr; // The address structure for a TCP socket
    SOCKET s;

    addr.sin_family = AF_INET;      // Address family
    addr.sin_port = htons (params->port);   // Assign port to this socket

    //Accept a connection from any IP using INADDR_ANY
    //You could pass inet_addr("0.0.0.0") instead to accomplish the
    //same thing. If you want only to watch for a connection from a
    //specific IP, specify that //instead.
    addr.sin_addr.s_addr = htonl (INADDR_ANY);

    (*params->addr)=addr;

    (*params->clilen) = sizeof(*params->addr);

    *params->clientID=0;

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
        while(/* *(params->connectionEstablished)==false || */true)
        {

            //Now we can start listening (allowing as many connections as possible to
            //be made at the same time using SOMAXCONN). You could specify any
            //integer value equal to or lesser than SOMAXCONN instead for custom
            //purposes). The function will not //return until a connection request is
            //made
            listen(s, SOMAXCONN);



            *params->newsockfd = accept(s, (struct sockaddr *) &(params->addr), (params->clilen));
            if (*params->newsockfd < 0)
            {
                cerr<<"ERROR on accept: "<<WSAGetLastError()<<endl;
            }
            else
            {
                *(params->connectionEstablished)=true;
                cerr << "Client connected!"<<endl;
            }


            *params->clientID=*params->clientID+1;
            cerr << "new client: "<<(int)*params->clientID<<endl;

            //simulate received type 4 to add player in game
            infosSocket dummyS;
            dummyS.type=4;
            (*params->socketsReceived).push_back(dummyS);

            //increment the last client ID

            //send to all clients except the new one information that a new client is connected, with his id
            dummyS.type=4;
            dummyS.variable[0]=*params->clientID;
            (*params->socketsToSend).push_back(dummyS);

            //send to this client his id
            dummyS.type=5;
            dummyS.variable[0]=*params->clientID;
            int n = sendSocket(params->tcp,*params->newsockfd,(char*)&dummyS, sizeof(dummyS),0,(struct sockaddr *) (params->addr), (*params->clilen));
            if (n < 0)
                cerr<<"ERROR writing to conn socket: "<<WSAGetLastError()<<endl;

            //add new client to client list.
            infosClient ic;
            ic.id=*params->clientID;
            ic.lastHeardFrom.reset();

            ic.sock=new int;
            *ic.sock=(*params->newsockfd);

            ic.addr=new sockaddr_in;
            *ic.addr=addr;


            ic.clilen=sizeof(ic.addr);

            (*params->clients).push_back(ic);


            //close socket. (why?)
            close(s);

            SDL_Delay(100);
        }
    }
    else//udp
    {
         *params->newsockfd  = socket(AF_INET, SOCK_DGRAM, 0); //Create socket udp
        bind(*params->newsockfd, (SOCKADDR*)&addr, (*params->clilen));

        cerr<<"waiting for client..."<<endl;
        infosSocket infosRecu;

        //waiting for client to connect
        while(*(params->connectionEstablished)==false)
        {
            int n = receiveSocket(params->tcp,*params->newsockfd, (char*)&infosRecu,sizeof(infosRecu), 0,(struct sockaddr *) (params->addr), (params->clilen));

            if (n < 0)
                cerr<<"ERROR reading from conn socket: "<<WSAGetLastError()<<endl;
            if(infosRecu.type==4)//client connect
                *(params->connectionEstablished)=true;
        }

        infosRecu.type=5;//serv response
        int n = sendSocket(params->tcp,*params->newsockfd,(char*)&infosRecu, sizeof(infosRecu),0,(struct sockaddr *) (params->addr), (*params->clilen));
        if (n < 0)
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

    while(params!=NULL/* && *(params->threadOn)*/)
    {
        infosSocket infosRecu;
        for(unsigned int i=0;i<(*params->clients).size();i++)
        {
            //int n = receiveSocket(params->tcp,*params->newsockfd, (char*)&infosRecu,sizeof(infosRecu), 0,(struct sockaddr *) (params->addr), (params->clilen));
            int n = receiveSocket(params->tcp,*(*params->clients)[i].sock, (char*)&infosRecu,sizeof(infosRecu), 0,(struct sockaddr *) (params->addr), (params->clilen));

            if (n < 0)
                cerr<<"ERROR reading from socket: "<<WSAGetLastError()<<endl;

            if(infosRecu.type!=-1)
            {
                //add received socket to queue
                (*params->socketsReceived).push_back(infosRecu);

                //cerr<<"transmiting socket type "<< (int)infosRecu.type<<endl;
                //add to send queue to send to other clients
                (*params->socketsToSend).push_back(infosRecu);
            }
        }

        SDL_Delay(SERV_WAIT_RECEIVE);
    }
    cerr << "End server receive thread"<<endl;
    return NULL;
}

void* serverSendThread(void* data)
{
    cerr << "Begin server send thread"<<endl;
    thread_params* params;
    params=(thread_params*)data;

    infosSocket infosS;

    //infinite while
    while(params!=NULL && *(params->threadOn))
    {
        //if there is something to send
        int nSendDirectly=(*params->socketsToSend).size();
        nSendDirectly=1;
        for(int j=0;j<nSendDirectly;j++)
        {
            if((*params->socketsToSend).size()>0)
            {
                //take first element of queue
                infosS=(*params->socketsToSend)[0];

                //int n = sendSocket(params->tcp,*params->newsockfd,(char*)&infosS, sizeof(infosS),0,(struct sockaddr *) (params->addr), (*params->clilen));
                for(unsigned int i=0;i<(*params->clients).size();i++)
                {
                    infosClient ic=(*params->clients)[i];
                    if(floor(infosS.variable[0])!=ic.id)//dont send to client who sent this to you
                    {
                        infosSocket s;
                        s=infosS;
                        //cerr<<" sending socket type "<<(int)s.type << ", 0: "<< s.variable[0]  << ", 1: "<< s.variable[1] << ", 2: "<< s.variable[2] << ", 3: "<< s.variable[3] <<endl;
                        //send
                        //int n = sendSocket(params->tcp,*params->newsockfd,(char*)&infosS, sizeof(infosS),0,(struct sockaddr *) (params->addr), (*params->clilen));
                        int n = sendSocket(params->tcp,*ic.sock,(char*)&infosS, sizeof(infosS),0,(struct sockaddr *) (ic.addr), (ic.clilen));
                        //check any error
                        if (n < 0)
                            cerr<<"ERROR writing to socket: "<<WSAGetLastError()<<endl;
                    }
                }
                //update queue
                for(unsigned int i=0;i<(*params->socketsToSend).size()-1;i++)
                    (*params->socketsToSend)[i]=(*params->socketsToSend)[i+1];
                if((*params->socketsToSend).size()>0)
                    (*params->socketsToSend).pop_back();
            }

        }

        SDL_Delay(SERV_WAIT_SEND);
    }

    close(*params->newsockfd);
    cerr << "End server send thread"<<endl;
    return NULL;
}
