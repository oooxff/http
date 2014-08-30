#include "AString.h"
#include "Socket.h"

#include <iostream>

using namespace std;


class HTTPDownLoader {
    public:
        HTTPDownLoader(uint16_t port, const char *IP);
        ~HTTPDownLoader();

        void download(void);
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

void HTTPDownLoader::download(void)
{
    int fd;
    ssize_t rn;
    char buffer[8192];

    mSocket->connect();
    fd = mSocket->fd();

    mStr->append("GET /201/test.webm HTTP/1.1\r\n");
    mStr->append("Accept: */*\r\n");
    mStr->append("User-Agent: A Simple File Downloader.\r\n");
    mStr->append("Host: 106.2.173.10\r\n");
    mStr->append("\r\n");

    write(fd, mStr->c_str(), strlen(mStr->c_str()));

    while(1) {
        rn = read(fd, buffer, sizeof(buffer));

        if (rn <= 0) {
            break;
        }

        buffer[rn] = 0;
        cout << buffer << endl;
    }
}

int main(int argc, char *argv[])
{
    HTTPDownLoader downloader(80, "106.2.173.10");
    downloader.download();

    return 0;
}

