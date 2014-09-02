#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "http_header_parser.h"

HTTPHeaderParser::HTTPHeaderParser(int fd)
    : mFd(fd),
      mLength(-1),
      mInit(0),
      mNum(-1) {
    }

HTTPHeaderParser::~HTTPHeaderParser()
{
}

void HTTPHeaderParser::readLine(char *buf, int size)
{
    char ch;
    int i = 0;
    
    while(read(mFd, &ch, sizeof(ch)) == 1) {
        if (ch != '\r') {
            buf[i ++] = ch;
        } else {
            buf[i] = 0;
            read(mFd, &ch, sizeof(ch));
            break;
        }
    }
}

void HTTPHeaderParser::parser(void)
{
    char buffer[1024];

    while(1) {
        readLine(buffer, sizeof(buffer));

        if (buffer[0] == 0)
            break;

        printf("[%s]\n", buffer);
        if (! strncmp(buffer, "Content-Length:", 15)) {
            sscanf(buffer, "Content-Length: %d", &mLength);
        } else if (! strncmp(buffer, "HTTP/1.1", 8)) {
            sscanf(buffer, "HTTP/1.1 %d OK", &mNum);
        }
    }
}

int HTTPHeaderParser::num(void)
{
    if(! mInit) {
        parser();
        mInit = 1;
    }

    return mNum;
}

int HTTPHeaderParser::length(void)
{
    if(! mInit) {
        parser();
        mInit = 1;
    }

    return mLength;
}

