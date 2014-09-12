#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <netdb.h>

int main(int argc, char *argv[])
{
    int i;
    struct hostent *host;

    host = gethostbyname("www.baidu.com");
    assert(host);
    
    printf("h_name: %s\n", host->h_name);

    for (i = 0; host->h_aliases[i]; i ++) {
        printf("h_aliases[%d] = %s\n", i, host->h_aliases[i]);
    }

    printf("h_length = %d\n", host->h_length);

    switch(host->h_addrtype) {
        case AF_INET:
            printf("h_addrtype = AF_INET\n");

            for (i = 0; host->h_addr_list[i]; i ++) {
                printf("h_addr_list[%d] = %s\n", i, host->h_addr_list[i]);
            }
            break;
    }
    return 0;
}

