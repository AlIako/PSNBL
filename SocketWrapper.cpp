#include "SocketWrapper.h"




SocketWrapper::SocketWrapper()
{
    untilSend.reset();
    timeTilResend=0;
}

