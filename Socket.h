#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TCPSocket {
    public:
        TCPSocket(uint16_t port, const char *IP);
        ~TCPSocket();

        void open(void);
        void connect(void);
        int fd(void);
        void close();
    private:
        int mFd;
        int mBackLog;
        uint16_t mPort;
        char mIP[16];
};

class UDPSocket {
};
#endif //_SOCKET_H_

