#ifndef _HTTP_URL_PARSER_H_
#define _HTTP_URL_PARSER_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

class http_url_parser {
    public:
        http_url_parser(const char *url);
        ~http_url_parser();

        bool isValide(void) { return true; };
        uint16_t port(void) { return mPort; };
        const char *host(void) { return mHost;}
        const char *path(void) { return mPath; };
        const char *searchpart(void) { return mSearchpart; };
        const char *scheme(void) { return mScheme; };

    private:
        void parser(void);
    private:
        char     *mURL;
        uint16_t mPort;
        char     *mHost;
        char     *mPath;
        char     *mSearchpart;
        char     *mScheme;
};

#endif //_HTTP_URL_PARSER_H_

