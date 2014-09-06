#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

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
        void save_as_file(int fd, int size);
    private:
        AString *mStr;
        const char *mFile;
        TCPSocket  *mSocket;
};

HTTPDownLoader::HTTPDownLoader(uint16_t port, const char *IP, const char *file)
    : mFile(file) {
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
    t_fd = open(mFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

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
    char buffer[1024];

    mSocket->connect();
    fd = mSocket->fd();
    HTTPHeaderParser parser(fd);

    snprintf(buffer, 1024, "GET /%s HTTP/1.1\r\n", mFile);
    mStr->append(buffer);
    mStr->append("Accept: */*\r\n");
    mStr->append("User-Agent: A Simple File Downloader.\r\n");
    mStr->append("Host: 10.0.0.201\r\n");
    mStr->append("\r\n");

    write(fd, mStr->c_str(), strlen(mStr->c_str()));

    if (parser.num() != 200) {
        cout << "Get " << mFile << " Failed, Error Code: " << parser.num() << endl;
        return;
    }
    cout << "Length: " << parser.length() << endl;
    save_as_file(fd, parser.length());
}

void url_download(const char *url)
{
    http_url_parser url_parser(url);
    HTTPDownLoader downloader(url_parser.port(), url_parser.host(), url_parser.path());
}
int main(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i ++) {
        url_download(argv[i]);
    }

    return 0;
}

