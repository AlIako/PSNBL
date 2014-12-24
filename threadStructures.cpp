#include "threadStructures.h"












int sendSocket(bool tcp,SOCKET s,const char* infosS,int sizeInfosS,int wut,const struct sockaddr* paramsin,int crecsize)
{
    return sendto(s, infosS, sizeInfosS, wut, paramsin, crecsize);
}


int receiveSocket(bool tcp,SOCKET s,char* infosS,int sizeInfosS,int wut,struct sockaddr* paramsin,int* crecsize)
{
    //tcp
    //WINSOCK_API_LINKAGE int PASCAL recv(SOCKET,char*,int,int);
    if(tcp)
        return recv (s, infosS,sizeInfosS, wut);

    //udp
    //WINSOCK_API_LINKAGE int PASCAL recvfrom(SOCKET,char*,int,int,struct sockaddr*,int*);
    //return recvfrom(params->sock,(char*)&infosRecu,sizeof(infosRecu),0,(SOCKADDR*)params->sin,&params->crecsize);
    return recvfrom(s, infosS, sizeInfosS, wut, paramsin, crecsize);


}



