#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "AString.h"
#include "Socket.h"
#include "http_header_parser.h"

#include <iostream>

using namespace std;


class HTTPDownLoader {
    public:
        HTTPDownLoader(uint16_t port, const char *IP);
        ~HTTPDownLoader();

        void download(void);
        void save_as_file(int fd, int size);
    private:
        AString *mStr;
        TCPSocket  *mSocket;
};

HTTPDownLoader::HTTPDownLoader(uint16_t port, const char *IP)
{
    mStr = new AString();
    mSocket = new TCPSocket(port, IP);
    mSocket->open();
}

HTTPDownLoader::~HTTPDownLoader()
{
    mSocket->close();
    delete mSocket; 
    delete mStr;
}

void HTTPDownLoader::save_as_file(int fd, int size)
{
    int t_fd;
    uint8_t *data;
    ssize_t rn = 0;
    
    data = (uint8_t *)malloc(4096);
    t_fd = open("test.webm", O_WRONLY);

    while(rn < size) {
        ssize_t r = read(fd, data, 4096);
        if (r <= 0) {
            printf("r: %d\n", r);
            return;
        }

        write(t_fd, data, r);
        rn += r;

    }

    close(t_fd);
}

void HTTPDownLoader::download(void)
{
    int fd;

    mSocket->connect();
    fd = mSocket->fd();
    HTTPHeaderParser parser(fd);

    mStr->append("GET /test.webm HTTP/1.1\r\n");
    mStr->append("Accept: */*\r\n");
    mStr->append("User-Agent: A Simple File Downloader.\r\n");
    mStr->append("Host: 10.0.0.201\r\n");
    mStr->append("\r\n");

    write(fd, mStr->c_str(), strlen(mStr->c_str()));
    cout << "Length: " << parser.length() << endl;
    save_as_file(fd, parser.length());
}

int main(int argc, char *argv[])
{
    HTTPDownLoader downloader(80, "10.0.0.201");
    downloader.download();

    return 0;
}

