#include "utils.h"
#include <assert.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "http_url_parser.h"

http_url_parser::http_url_parser(const char *url)
    : mURL(strdup(url)),
    mPort(80),
    mHost(0),
    mPath(0),
    mScheme(0),
    mHaveScheme(false) {
        parser();
    }

http_url_parser::~http_url_parser()
{
    free(mURL); free(mHost); free(mPath); free(mScheme);
}

void http_url_parser::parser_url_with_port(void)
{
    char *pos;
    char *url;
    char *port_pos;

    url = mHaveScheme? mURL + 7 : mURL;
    port_pos = strchr(url, ':');

    mHost = (char *)malloc(port_pos - url + 1);
    strncpy(mHost, url, port_pos - url);
    mHost[port_pos - url] = 0;
    mPort = atoi(port_pos + 1);

    pos = strchr(url, '/');

    if (! pos) {
        mPath = (char *)malloc(2);
        mPath[0] = '/'; mPath[1] = 0;
    } else {
        mPath = (char *)malloc(strlen(pos) + 1);
        strcpy(mPath, pos);
    }
}

void http_url_parser::parser_url_without_port(void)
{
    char *tmp;
    char *pos;

    tmp = mHaveScheme? mURL + 7 : mURL;
    pos = strchr(tmp, '/');

    if (! pos) {
        mHost = (char *)malloc(strlen(tmp) + 1);
        strcpy(mHost, tmp);
        mPath = (char *)malloc(2);
        mPath[0] = '/'; mPath[1] = 0;
    } else {
        mHost = (char *)malloc(pos - tmp + 1);
        strncpy(mHost, tmp, pos - tmp);
        mHost[pos - tmp] = 0;
        mPath = (char *)malloc(strlen(pos) + 1);
        strcpy(mPath, pos);
    }
}

bool http_url_parser::is_host_ip(void)
{
    int i;

    for (i = 0; mHost[i]; i ++) {
        if (mHost[i] != '.' && (! Utils::is_digit(mHost[i]))) {
            return false;
        }
    }

    return true;
}

void http_url_parser::parser_host_ip(void)
{
    struct in_addr ip;
    struct hostent *host;

    host = gethostbyname(mHost);
    assert(host);
    
    printf("h_name: %s\n", host->h_name);
    bcopy(host->h_addr, &(ip.s_addr), host->h_length);
    printf("IP: %s\n", inet_ntoa(ip));
    mHostIP = (char *)malloc(16);
    strcpy(mHostIP, inet_ntoa(ip));
}

void http_url_parser::parser(void)
{
    int i;
    char *tmp;
    bool have_port = false;

    /*
     * URL example.
     * http://<host>:<port>/<path>?<searchpart>
     * http://10.0.0.201/video/mp4/test.mp4?id=1&ts=10000
     */

    mScheme = (char *)malloc(sizeof("http"));
    strcpy(mScheme, "http");

    mHaveScheme = ! strncmp(mURL, "http://", 7);
    tmp = mHaveScheme? mURL + 7 : mURL;

    for (i = 0; tmp[i] != '/' && tmp[i]; i ++) {
        if (tmp[i] == ':') {
            have_port = true;
            break;
        }
    }

    if (have_port) {
        parser_url_with_port();
    } else {
        parser_url_without_port();
    }

    if(! is_host_ip()) {
        parser_host_ip();
    }
}
