#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <netdb.h>

int main(int argc, char *argv[])
{
    struct hostent *host;
    struct in_addr ip;

    host = gethostbyname("www.baidu.com");
    assert(host);
    
    printf("h_name: %s\n", host->h_name);
    bcopy(host->h_addr, &(ip.s_addr), host->h_length);
    printf("IP: %s\n", inet_ntoa(ip));
    return 0;
}

