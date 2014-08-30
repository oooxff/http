#include "Socket.h"

TCPSocket::TCPSocket(uint16_t port, const char *IP)
    : mFd(-1),
      mBackLog(1024),
      mPort(80) {
          strcpy(mIP, IP);
      }

TCPSocket::~TCPSocket()
{
    if (mFd != -1) {
        ::close(mFd);
    }
}

void TCPSocket::open(void)
{
    mFd = socket(AF_INET, SOCK_STREAM, 0);
}

void TCPSocket::connect(void)
{
    struct sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_port = htons(mPort);
    inet_aton(mIP, &servaddr.sin_addr);

    ::connect(mFd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
}

int TCPSocket::fd(void)
{
    return mFd;
}

void TCPSocket::close(void)
{
    ::close(mFd);
    mFd = -1;
}
