#include "http_download.h"

HTTPDownLoader::HTTPDownLoader(uint16_t port, const char *IP, const char *file)
    : mFile(file),
    mIP(IP) {
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

void HTTPDownLoader::show_download_percent(ssize_t rn, int size)
{
#if __x86_64__
    printf("Downloading: %02ld%%\r", 100 * rn / size);
#else
    printf("Downloading: %02d%%\r", 100 * rn / size);
#endif
}

void HTTPDownLoader::save_as_file(int fd, int size)
{
    int t_fd;
    char *file;
    uint8_t *data;
    ssize_t rn = 0;
    
    file = (char *)strrchr(mFile, '/');
    t_fd = open(file? file + 1 : mFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    data = (uint8_t *)malloc(4096);
    while(rn < size) {
        ssize_t r = read(fd, data, 4096);
        if (r < 0) {
            printf("download: read failed.\n");
            return;
        }

        show_download_percent(rn, size);
        write(t_fd, data, r);
        rn += r;

    }
    show_download_percent(rn, size);
    putchar('\n');

    close(t_fd);
}

void HTTPDownLoader::download(void)
{
    char buffer[1024];

    mSocket->connect();

    snprintf(buffer, 1024, "GET %s HTTP/1.1\r\n", mFile);
    mStr->append(buffer);
    mStr->append("Accept: */*\r\n");
    mStr->append("User-Agent: A Simple File Downloader.\r\n");
    snprintf(buffer, 1024, "Host: %s\r\n", mIP);
    mStr->append(buffer);
    mStr->append("\r\n");

    printf("C -> S: \n%s\n", mStr->c_str());

    write(mSocket->fd(), mStr->c_str(), strlen(mStr->c_str()));
    HTTPHeaderParser parser(mSocket->fd());

    if (parser.num() != 200) {
        cout << "Get " << mFile << " Failed, Error Code: " << parser.num() << endl;
        return;
    }
    cout << "Length: " << parser.length() << endl;
    save_as_file(mSocket->fd(), parser.length());
}


