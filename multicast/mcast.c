#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

int port = 6789;

int main(int argc, char **argv)
{
    int socketfd;
    struct sockaddr_in address;

    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == socketfd)
    {
        perror("Opening socket");
        exit(EXIT_FAILURE);
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("224.0.0.1");
    address.sin_port = htons(port);

    //starting Mcast transmit...
    while(1)
    {
        if (sendto(socketfd, "test from broadcast", sizeof("test from broadcast"), 0,(struct sockaddr *)&address, sizeof(address)) < 0)
        {
            perror("sendto");
            exit(EXIT_FAILURE);
        }
        sleep(2);
    }
    exit(EXIT_SUCCESS);
}
