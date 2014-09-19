#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

char *host_name = "224.0.0.1";
int port = 6789;

int main(int argc, char **argv)
{
    int socketfd;
    struct sockaddr_in sin;
    struct ip_mreq command;
    int loop, reuse;
    int iter = 0;
    socklen_t sin_len;
    struct hostent *server_host_name;
    char message[256];

    if ((server_host_name = gethostbyname(host_name)) == 0)
    {
        perror("gethostbyname");
        exit(EXIT_FAILURE);
    }
    //printf("server_host_name = %s\n", server_host_name);

    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == socketfd)
    {
        perror("Opening socket");
        exit(EXIT_FAILURE);
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(port);

    reuse = 1;
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
    {
        perror("setsockopt: SO_REUSEADDR");
        exit(EXIT_FAILURE);
    }

    if (bind(socketfd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    loop = 1;
    if (setsockopt(socketfd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop)) < 0)
    {
        perror("setsockopt: IP_MULTICAST_LOOP");
        exit(EXIT_FAILURE);
    }

    command.imr_multiaddr.s_addr = inet_addr("224.0.0.1");
    command.imr_interface.s_addr = htonl(INADDR_ANY);
    if (command.imr_multiaddr.s_addr == -1)
    {
        perror("224.0.0.1 not a legal multicast address.");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(socketfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &command, sizeof(command)) < 0)
    {
        perror("setsockopt: IP ADD_MEMBERSHIP");
    }

    while(iter < 8)
    {
        sin_len = sizeof(sin);
        if (recvfrom(socketfd, message, 256, 0, (struct sockaddr *)&sin, &sin_len) == -1)
        {
            perror("recvfrom");
        }

        printf("Response #%-2d from server: %s\n", iter++, message);
        sleep(2);
    }

    if (setsockopt(socketfd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &command, sizeof(command)) < 0)
    {
        perror("setsockopt: IP_DROP_MEMBERSHIP");
    }

    close(socketfd);
    exit(EXIT_SUCCESS);
}

