#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "AString.h"
#include "Socket.h"
#include "http_header_parser.h"
#include "http_url_parser.h"

#include <iostream>

using namespace std;


class HTTPDownLoader {
    public:
        HTTPDownLoader(uint16_t port, const char *IP, const char *file);
        ~HTTPDownLoader();

        void download(void);

    private:
        void show_download_percent(ssize_t rn, int size);
        void save_as_file(int fd, int size);

    private:
        AString *mStr;
        const char *mFile;
        const char *mIP;
        TCPSocket  *mSocket;
};

