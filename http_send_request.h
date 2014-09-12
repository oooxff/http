#ifndef _HTTP_SEND_REQUEST_H_
#define _HTTP_SEND_REQUEST_H_

#include "AString.h"
#include "Socket.h"
#include "http_url_parser.h"

class http_send_request {
    public:
        http_send_request(const char *url);
        ~http_send_request();

        void send_request(const char *req);
        void dump_response(void);
    private:
        void send_options_request(void);
    private:
        const char *mURL;
        AString    *mRequest;
        TCPSocket  *mTCPSocket;
        http_url_parser *mParser;
};
#endif //_HTTP_SEND_REQUEST_H_
