#include <cstdio>

#include "http_send_request.h"
#include "http_url_parser.h"

http_send_request::http_send_request(const char *url)
    : mURL(url) {
        mRequest = new AString("");
        mParser = new http_url_parser(mURL);
        mTCPSocket = new TCPSocket(mParser->port(), mParser->host());

        mTCPSocket->open();
        mTCPSocket->connect();
    }

void http_send_request::send_options_request(void)
{
    char buffer[1024];

    mRequest->append("OPTIONS * HTTP/1.1\r\n");

    snprintf(buffer, sizeof(buffer), "HOST: %s\r\n", mParser->host());
    mRequest->append(buffer);
    mRequest->append("\r\n");
    
    printf("\n%s\n", mRequest->c_str());

    write(mTCPSocket->fd(), mRequest->c_str(), strlen(mRequest->c_str()));

}

void http_send_request::send_request(const char *req)
{
    if (! strcmp(req, "OPTIONS")) {
        send_options_request();
    } else {
        
    }
}

void http_send_request::dump_response(void)
{
    ssize_t rn;
    char buffer[1024];

    while((rn = read(mTCPSocket->fd(), buffer, 1024)) != 0) {
        if (rn < 0) {
            printf("read error.\n");
            break;
        }

        buffer[rn] = 0;
        printf("%s", buffer);
    }
}

http_send_request::~http_send_request()
{
    delete mRequest;
    delete mTCPSocket;
    delete mParser;
}
