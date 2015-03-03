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
    {
        //return false;
    }

    //Did we get the right Winsock version?
    if (wsadata.wVersion != 0x0202)
    {
        WSACleanup(); //Clean up Winsock
        //return false;
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
            //return false; //Couldn't create the socket
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
        infosRecu.confirmationID=-1;
        infosRecu.type=4;//client connect
        cerr << "connecting..."<<endl;

        *params->newsockfd  = socket(AF_INET, SOCK_DGRAM, 0); //Create socket udp

        //send connection request to serv
        int n = sendSocket(params->tcp,*params->newsockfd,(char*)&infosRecu, sizeof(infosRecu),0,(struct sockaddr *) (params->addr), (*params->clilen));
        if (n < 0)
            cerr<<"ERROR writing from conn socket: "<<WSAGetLastError()<<endl;

        //receive answer from serv
        n = receiveSocket(params->tcp,*params->newsockfd, (char*)&infosRecu,sizeof(infosRecu), 0,(struct sockaddr *) (params->addr), (params->clilen));

        if (n < 0)
            cerr<<"ERROR reading to conn socket: "<<WSAGetLastError()<<endl;



        if(infosRecu.type==5)//serv response
            *(params->connectionEstablished)=true;


        (*params->clientID)=infosRecu.variable[0];
        cerr<<"server responded. my client id is "<< (int)infosRecu.variable[0]<<endl;
        (*params->socketsReceived).push_back(infosRecu);


        SDL_Delay(50);


        cerr << "Connection succesful!"<<endl;
    }


    cerr << "End client connection thread"<<endl;
    return NULL;
}


void* clientReceiveThread(void* data)
{
    cerr << "Begin client receive thread"<<endl;
    thread_params* params;
    params=(thread_params*)data;

    //receive informations from server
    while(params!=NULL && *(params->threadOn))
    {
        //sem_wait(params->mutex);

        infosSocket infosRecu;
        int n = receiveSocket(params->tcp,*params->newsockfd, (char*)&infosRecu,sizeof(infosRecu), 0,(struct sockaddr *) (params->addr), (params->clilen));
        if (n < 0)
            cerr<<"ERROR reading from socket: "<<WSAGetLastError()<<endl;

        //add received socket to queue
        if(infosRecu.type!=-1)
        {
            cerr<<"-----received socket type "<<(int)infosRecu.type << ", 0: "<< infosRecu.variable[0]  << ", 1: "<< infosRecu.variable[1] << ", 2: "<< infosRecu.variable[2] << ", 3: "<< infosRecu.variable[3] <<endl;

            //add to list only if you didn't already receive that or if not important socket
            bool alreadyReceived=false;

            if(infosRecu.confirmationID!=-1)//important socket
            {
                for(unsigned int j=0;!alreadyReceived && j<(*params->confirmIDreceived).size();j++)
                {
                    //cerr<<"c: "<<infosRecu.confirmationID<<" -- "<<(*params->confirmIDreceived)[j]<<endl;
                    if(infosRecu.confirmationID==(*params->confirmIDreceived)[j].idConfirm
                       && infosRecu.variable[0]==(*params->confirmIDreceived)[j].idClient)//already received
                        alreadyReceived=true;
                }
            }
            //handle socket only if not already received
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
            }
            else
            {
                cerr<<"already received; not handling again."<<endl;
            }


            //if socket needs confirmation; send it back.to the server
            if(infosRecu.confirmationID!=-1 && infosRecu.type!=11)
            {
                infosSocket infosConfirmation;
                infosConfirmation.type=11;
                infosConfirmation.confirmationID=infosRecu.confirmationID;
                infosConfirmation.variable[0]=*params->clientID;//YOUR ID

                SocketWrapper sw;
                sw.socket=infosConfirmation;

                (*params->socketWrappersToSend).push_back(sw);

                cerr<<"important socket " <<infosConfirmation.confirmationID << " (type " << (int)infosRecu.type <<") received"<<endl;
            }

            //if I received confirmation, delete socket that needed this confirmation so it wont be sent again
            if(infosRecu.type==11)
            {
                cerr<<"received confirmation " << infosRecu.confirmationID<< "!"<<endl;
                for(unsigned int j=0;j<(*params->socketWrappersToSend).size();j++)
                {
                    SocketWrapper sw=(*params->socketWrappersToSend)[j];
                    if(sw.socket.confirmationID==infosRecu.confirmationID)
                    {
                        cerr<<"important socket "<< infosRecu.confirmationID<< " deleted."<<endl;

                        (*params->socketWrappersToSend).erase((*params->socketWrappersToSend).begin()+j);
                    }
                }
            }
        }

        SDL_Delay(CLIENT_WAIT_RECEIVE);
        //sem_post(params->mutex);
    }
    cerr << "End client receive thread"<<endl;
    return NULL;
}

void* clientSendThread(void* data)
{
    cerr << "Begin client send thread"<<endl;
    thread_params* params=(thread_params*)data;

    infosSocket infosS;

    while(params!=NULL && *(params->threadOn))
    {
        //sem_wait(params->mutex);

        //if there is something to send
        if((*params->socketWrappersToSend).size()>0)
        {
            SocketWrapper sw=(*params->socketWrappersToSend)[0];


            sw.untilSend.couler();
            if(sw.untilSend.ecouler(sw.timeTilResend))//is it time to send it?
            {
                //take first element of queue
                infosS=sw.socket;


                //infosSocket s=infosS;
                cerr<<"-----sending socket type "<<(int)infosS.type << ", 0: "<< infosS.variable[0]  << ", 1: "<< infosS.variable[1] << ", 2: "<< infosS.variable[2] << ", 3: "<< infosS.variable[3] <<endl;

                //send
                int n = sendSocket(params->tcp,*params->newsockfd,(char*)&infosS, sizeof(infosS),0,(struct sockaddr *) (params->addr), (*params->clilen));
                //check any error
                if (n < 0)
                    cerr<<"ERROR writing to socket: "<<WSAGetLastError()<<endl;


                //update queue
                //if socket doenst need confirmation (or is a confirmation for a client that needs one), delete it from quere
                if(infosS.confirmationID==-1 || infosS.type==11)
                {
                    if(infosS.type==11)
                        cerr<<"confirmation "<< infosS.confirmationID<< "sent!"<<endl;


                    (*params->socketWrappersToSend).erase((*params->socketWrappersToSend).begin());
                }
                else//if socket NEEDS confirmation, put it at the end of the queue, so that it will be sent again
                {
                    //send it a bit later
                    sw.untilSend.reset();
                    sw.timeTilResend=100;

                    cerr<<"important socket "<< infosS.confirmationID<<" (type "<< (int)infosS.type <<") sent! confirmation queued."<<endl;

                    for(unsigned int i=0;i<(*params->socketWrappersToSend).size()-1;i++)
                        (*params->socketWrappersToSend)[i]=(*params->socketWrappersToSend)[i+1];
                    (*params->socketWrappersToSend)[(*params->socketWrappersToSend).size()-1]=sw;
                }
            }
            else// if not time to send, put it at the end of the list
            {
                for(unsigned int i=0;i<(*params->socketWrappersToSend).size()-1;i++)
                    (*params->socketWrappersToSend)[i]=(*params->socketWrappersToSend)[i+1];
                (*params->socketWrappersToSend)[(*params->socketWrappersToSend).size()-1]=sw;
            }
        }

        SDL_Delay(CLIENT_WAIT_SEND);
        //sem_post(params->mutex);
    }


    close(*params->newsockfd);
    cerr << "End client send thread"<<endl;
    return NULL;
}



