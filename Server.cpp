#include "Server.h"

#define SERV_WAIT_SEND 7
#define SERV_WAIT_RECEIVE 2

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
        //return false; //For some reason we couldn't start Winsock
    }

    if (w.wVersion != 0x0202) //Wrong Winsock version?
    {
        WSACleanup ();
        //return false;
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
            //return false; //Don't continue if we couldn't create a //socket!!
        }

        if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
        {
            cerr << "Couldn't bind"<<endl;
           //We couldn't bind (this will happen if you try to bind to the same
           //socket more than once)
            //return false;
        }
        while(/* *(params->connectionEstablished)==false || */true)
        {
            //sem_wait(params->mutex);

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
            dummyS.confirmationID=-1;
            dummyS.type=4;
            (*params->socketsReceived).push_back(dummyS);

            //increment the last client ID

            //send to all clients except the new one information that a new client is connected, with his id
            dummyS.type=4;
            dummyS.variable[0]=*params->clientID;
            //(*params->socketsToSend).push_back(dummyS);
            for(unsigned int i=0;i<(*params->clients).size();i++)
            {
                infosClient ic=(*params->clients)[i];
                if(floor(dummyS.variable[0])!=ic.id)//dont send to client who sent this to you
                {
                    SocketWrapper sw;
                    sw.socket=dummyS;
                    sw.client=ic;
                    (*params->socketWrappersToSend).push_back(sw);
                }
            }

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

            //sem_post(params->mutex);
        }
    }
    else//udp
    {
        *params->newsockfd  = socket(AF_INET, SOCK_DGRAM, 0); //Create socket udp
        bind(*params->newsockfd, (SOCKADDR*)&addr, (*params->clilen));
        cerr<<"waiting for client..."<<endl;
        //waiting for client to connect

        while(/* *(params->connectionEstablished)==false*/  *params->serverOn)
        {
            //sem_wait(params->mutex);

            infosSocket infosRecu;
            int n = receiveSocket(params->tcp,*params->newsockfd, (char*)&infosRecu,sizeof(infosRecu), 0,(struct sockaddr *) (params->addr), (params->clilen));

            if (n < 0)
                cerr<<"ERROR reading from conn socket: "<<WSAGetLastError()<<endl;
            if(infosRecu.type==4)//client connect
            {


                *params->clientID=*params->clientID+1;
                cerr << "new client: "<<(int)*params->clientID<<endl;

                //simulate received type 4 to add player in game
                infosSocket dummyS;
                dummyS.confirmationID=-1;
                dummyS.type=4;
                (*params->socketsReceived).push_back(dummyS);

                //increment the last client ID

                //send to all clients except the new one information that a new client is connected, with his id
                dummyS.type=4;
                dummyS.variable[0]=*params->clientID;
                for(unsigned int i=0;i<(*params->clients).size();i++)
                {
                    infosClient ic=(*params->clients)[i];
                    if(floor(dummyS.variable[0])!=ic.id)//dont send to client who sent this to you
                    {
                        SocketWrapper sw;
                        sw.socket=dummyS;
                        sw.client=ic;
                        (*params->socketWrappersToSend).push_back(sw);
                    }
                }

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
                *ic.addr=(*params->addr);


                ic.clilen=(*params->clilen);

                (*params->clients).push_back(ic);


                SDL_Delay(100);
                cerr<<"end connection with this client "<<endl;
                *(params->connectionEstablished)=true;
            }
            else (*params->socketsReceived).push_back(infosRecu);


            //sem_post(params->mutex);

            break;
        }

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
        //sem_wait(params->mutex);

        infosSocket infosRecu;
        //for(unsigned int i=0;i<(*params->clients).size();i++)
        for(unsigned int i=0;i<1;i++)
        {
            infosRecu.type=-1;
            int n = receiveSocket(params->tcp,*params->newsockfd, (char*)&infosRecu,sizeof(infosRecu), 0,(struct sockaddr *) (params->addr), (params->clilen));
            //int n = receiveSocket(params->tcp,*(*params->clients)[i].sock, (char*)&infosRecu,sizeof(infosRecu), 0,(struct sockaddr *) (params->addr), (params->clilen));

            if (n < 0)
                cerr<<"ERROR reading from socket: "<<WSAGetLastError()<<endl;

            if(infosRecu.type!=-1)
            {
                cerr<<"-----received socket type "<<(int)infosRecu.type << ", 0: "<< infosRecu.variable[0]  << ", 1: "<< infosRecu.variable[1] << ", 2: "<< infosRecu.variable[2] << ", 3: "<< infosRecu.variable[3] <<endl;
                //add received socket to queue


                if(infosRecu.type==4)//client connect
                {


                    *params->clientID=*params->clientID+1;
                    cerr << "new client: "<<(int)*params->clientID<<endl;

                    //simulate received type 4 to add player in game
                    infosSocket dummyS;
                    dummyS.confirmationID=-1;
                    dummyS.type=4;
                    (*params->socketsReceived).push_back(dummyS);

                    //increment the last client ID

                    //send to all clients except the new one information that a new client is connected, with his id
                    dummyS.type=4;
                    dummyS.variable[0]=*params->clientID;
                    for(unsigned int i=0;i<(*params->clients).size();i++)
                    {
                        infosClient ic=(*params->clients)[i];
                        if(floor(dummyS.variable[0])!=ic.id)//dont send to client who sent this to you
                        {
                            SocketWrapper sw;
                            sw.socket=dummyS;
                            sw.client=ic;
                            (*params->socketWrappersToSend).push_back(sw);
                        }
                    }

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
                    *ic.addr=(*params->addr);


                    ic.clilen=(*params->clilen);

                    (*params->clients).push_back(ic);


                    //SDL_Delay(100);
                    cerr<<"end connection with this client "<<endl;
                }

                //player disconnect
                if(infosRecu.type==12)
                {
                    cerr<<"Player "<< infosRecu.variable[0]<<" disconnected."<<endl;
                    //delete from client list
                    for(unsigned int j=0;j<(*params->clients).size();j++)
                    {
                        if((*params->clients)[j].id==infosRecu.variable[0])
                        {
                            (*params->clients).erase((*params->clients).begin()+j);
                        }
                    }
                    //delete all sockets to send to this client
                    for(unsigned int j=0;j<(*params->socketWrappersToSend).size();j++)
                    {
                        if((*params->socketWrappersToSend)[j].client.id==infosRecu.variable[0])
                        {
                            (*params->socketWrappersToSend).erase((*params->socketWrappersToSend).begin()+j);
                        }
                    }
                }




                //add to list only if you didn't already receive that or if not important socket
                bool alreadyReceived=false;

                if(infosRecu.confirmationID!=-1)
                {
                    for(unsigned int j=0;!alreadyReceived && j<(*params->confirmIDreceived).size();j++)
                    {
                        if(infosRecu.confirmationID==(*params->confirmIDreceived)[j].idConfirm
                        && infosRecu.variable[0]==(*params->confirmIDreceived)[j].idClient)//already received
                        {
                            cerr<<"socket "<<infosRecu.confirmationID <<" already received "<<endl;
                            alreadyReceived=true;
                        }
                    }
                }

                if(!alreadyReceived)
                {
                    if(infosRecu.confirmationID!=-1 && infosRecu.type!=11)
                    {
                        cID cid;
                        cid.idClient=infosRecu.variable[0];
                        cid.idConfirm=infosRecu.confirmationID;
                        (*params->confirmIDreceived).push_back(cid);
                    }


                    (*params->socketsReceived).push_back(infosRecu);


                    //cerr<<"transmiting socket type "<< (int)infosRecu.type<<endl;

                    //add to send queue to send to other clients
                    //(*params->socketsToSend).push_back(infosRecu);
                    for(unsigned int j=0;j<(*params->clients).size();j++)
                    {
                        infosClient ic=(*params->clients)[j];
                        if((*params->clients)[j].id!=infosRecu.variable[0])//dont send to client who sent this to you
                        {
                            SocketWrapper sw;
                            sw.socket=infosRecu;
                            sw.client=ic;
                            (*params->socketWrappersToSend).push_back(sw);
                        }
                    }
                }
                else
                {
                    cerr<<"already received; not handling again."<<endl;
                }


                //if socket needs confirmation; send it back.to this particular client only
                if(infosRecu.confirmationID!=-1 && infosRecu.type!=11)
                {
                    infosSocket infosConfirmation;
                    infosConfirmation.type=11;
                    infosConfirmation.confirmationID=infosRecu.confirmationID;
                    infosConfirmation.variable[0]=infosRecu.variable[0];//same id as socket received

                    SocketWrapper sw;
                    sw.socket=infosConfirmation;
                    //find which client
                    for(unsigned int j=0;j<(*params->clients).size();j++)
                    {
                        if((*params->clients)[j].id==infosRecu.variable[0])
                            sw.client=(*params->clients)[j];
                    }
                    (*params->socketWrappersToSend).push_back(sw);

                    cerr<<"important socket " <<infosConfirmation.confirmationID << " (type " << (int)infosRecu.type <<") received"<<endl;
                }

                //if I received confirmation, delete socket that needed this confirmation so it wont be sent again
                if(infosRecu.type==11)
                {
                    //GO SEMAPHORE
                    if((*params->modifArray))
                        sem_wait(params->mutex);
                    (*params->modifArray)=true;

                    cerr<<"received confirmation " << infosRecu.confirmationID<< "!"<<endl;
                    for(unsigned int j=0;j<(*params->socketWrappersToSend).size();j++)
                    {
                        SocketWrapper sw=(*params->socketWrappersToSend)[j];//THIS LINE CRASH
                        if(sw.socket.confirmationID==infosRecu.confirmationID && sw.client.id==infosRecu.variable[0])//same ID, same client
                        {
                            cerr<<"important socket "<< infosRecu.confirmationID<< " deleted."<<endl;
                            (*params->socketWrappersToSend).erase((*params->socketWrappersToSend).begin()+j);
                        }
                    }
                    cerr<<"list of important wrappers to send:"<<endl;
                    for(unsigned int j=0;j<(*params->socketWrappersToSend).size();j++)
                    {
                        SocketWrapper sw=(*params->socketWrappersToSend)[j];
                        if(sw.socket.confirmationID!=-1 && sw.socket.type!=11)
                        {
                            cerr<<"type: "<<(int)sw.socket.type<<", "<<sw.socket.confirmationID<<endl;
                        }
                    }
                    cerr<<endl;
                    //END SEMAPHORE

                    (*params->modifArray)=false;
                    sem_post(params->mutex);
                }
            }
        }

        SDL_Delay(SERV_WAIT_RECEIVE);

        //sem_post(params->mutex);
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
        //GO SEMAPHORE
        sem_wait(params->mutex);
        (*params->modifArray)=true;

        //if there is something to send
        int nSendDirectly=(*params->socketWrappersToSend).size();
        nSendDirectly=1;
        for(int j=0;j<nSendDirectly;j++)
        {
            if((*params->socketWrappersToSend).size()>0)
            {
                //take first element of queue
                SocketWrapper sw=(*params->socketWrappersToSend)[j];


                sw.untilSend.couler();
                if(sw.untilSend.ecouler(sw.timeTilResend))//is it time to send it?
                {
                    infosS=sw.socket;

                    //int n = sendSocket(params->tcp,*params->newsockfd,(char*)&infosS, sizeof(infosS),0,(struct sockaddr *) (params->addr), (*params->clilen));
                    infosClient ic=sw.client;

                    cerr<<"-----sending socket type "<<(int)infosS.type << ", 0: "<< infosS.variable[0]  << ", 1: "<< infosS.variable[1] << ", 2: "<< infosS.variable[2] << ", 3: "<< infosS.variable[3] <<endl;
                    //send
                    //int n = sendSocket(params->tcp,*params->newsockfd,(char*)&infosS, sizeof(infosS),0,(struct sockaddr *) (params->addr), (*params->clilen));
                    int n = sendSocket(params->tcp,*ic.sock,(char*)&infosS, sizeof(infosS),0,(struct sockaddr *) (ic.addr), (ic.clilen));
                    //check any error
                    if (n < 0)
                        cerr<<"ERROR writing to socket: "<<WSAGetLastError()<<endl;



                    //update queue
                    //if socket doenst need confirmation (or is a confirmation for a client that needs one), delete it from quere
                    if(infosS.confirmationID==-1 || infosS.type==11)//delete || true to make safe trnasmission work back
                    {
                        (*params->socketWrappersToSend).erase((*params->socketWrappersToSend).begin());
                    }
                    else//if socket NEEDS confirmation, put it at the end of the queue, so that it will be sent again
                    {
                        cerr<<"important socket "<<sw.socket.confirmationID <<" (type "<< (int)sw.socket.type<<") sent! puting it at the end of the queue"<<endl;
                        //send it a bit later
                        sw.untilSend.reset();
                        sw.timeTilResend=200;


                        for(unsigned int i=0;i<(*params->socketWrappersToSend).size()-1;i++)
                            (*params->socketWrappersToSend)[i]=(*params->socketWrappersToSend)[i+1];
                        (*params->socketWrappersToSend)[(*params->socketWrappersToSend).size()-1]=sw;
                    }
                }
                else// if not time to send, put it at the end of the list
                {
                    for(unsigned int i=0;i<(*params->socketWrappersToSend).size()-1;i++)
                        (*params->socketWrappersToSend)[i]=(*params->socketWrappersToSend)[i+1];
                    (*params->socketWrappersToSend)[(*params->socketWrappersToSend).size()-1]=sw;//THIS LINE CRASH
                }
            }

        }

        //END SEMAPHORE

        (*params->modifArray)=false;
        sem_post(params->mutex);
        SDL_Delay(SERV_WAIT_SEND);

    }

    close(*params->newsockfd);
    cerr << "End server send thread"<<endl;
    return NULL;
}
