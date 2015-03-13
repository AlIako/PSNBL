#include "threadStructures.h"












int sendSocket(bool tcp,SOCKET s,const char* infosS,int sizeInfosS,int wut,const struct sockaddr* paramsin,int crecsize)
{
    return sendto(s, infosS, sizeInfosS, wut, paramsin, crecsize);
}


int receiveSocket(bool tcp,SOCKET s,char* infosS,int sizeInfosS,int wut,struct sockaddr* paramsin,int* crecsize, int timeoutValue)
{
    fd_set fds ;

    // Set up the file descriptor set.
    FD_ZERO(&fds) ;
    FD_SET(s, &fds) ;

    timeval tv;
    tv.tv_sec = timeoutValue;
    tv.tv_usec = 0;

    // Wait until timeout or data received.
    int n = select ( s, &fds, NULL, NULL, &tv ) ;
    //int n = select ( s, NULL, NULL, NULL, &tv ) ;
    if ( n == 0)
    {
      cerr<<"Timeout select().."<<endl;
      return 0 ;
    }
    else if( n == -1 )
    {
      cerr<<"Error select().."<<endl;
      return -1;
    }

    //tcp
    //WINSOCK_API_LINKAGE int PASCAL recv(SOCKET,char*,int,int);
    if(tcp)
        return recv (s, infosS,sizeInfosS, wut);

    //udp
    //WINSOCK_API_LINKAGE int PASCAL recvfrom(SOCKET,char*,int,int,struct sockaddr*,int*);
    //return recvfrom(params->sock,(char*)&infosRecu,sizeof(infosRecu),0,(SOCKADDR*)params->sin,&params->crecsize);
    return recvfrom(s, infosS, sizeInfosS, wut, paramsin, crecsize);


}



