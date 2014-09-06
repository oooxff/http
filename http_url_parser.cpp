#include "http_url_parser.h"

http_url_parser::http_url_parser(const char *url)
    : mURL(strdup(url)),
    mPort(80),
    mHost(0),
    mPath(0),
    mSearchpart(0),
    mScheme(0) {
        parser();
    }

http_url_parser::~http_url_parser()
{
    free(mURL); free(mHost); free(mPath);
    free(mSearchpart); free(mScheme);
}

void http_url_parser::parser(void)
{
    int i = 0;
    char *ret;
    /*
     * URL example.
     * http://<host>:<port>/<path>?<searchpart>
     */

    mScheme = (char *)malloc(sizeof("http"));
    strcpy(mScheme, "http");

    bool have_scheme = ! strncmp(mURL, "http://", 7);

    mURL = have_scheme? mURL + 7 : mURL;

    while((ret = strsep(&mURL, "/")) != NULL) {
        if (i == 0) {
            int m = 0;
            char *r;

            while((r = strsep(&ret, ":")) != NULL) {
                if (m == 0) {
                    mHost = (char *)malloc(strlen(r) + 1);
                    strcpy(mHost, r); m ++;
                } else if (m == 1) {
                    mPort = atoi(r); m ++;
                }
            }

            i ++;
        } else if (i == 1) {
            int n = 0;
            char *r;

            while((r = strsep(&ret, "?")) != NULL) {
                if (n == 0) {
                    mPath = (char *)malloc(strlen(r) + 1);
                    strcpy(mPath, r); n ++;
                } else if (n == 1) {
                    mSearchpart = (char *)malloc(strlen(r) + 1);
                    strcpy(mSearchpart, r); n ++;
                }
            }

            i ++;
        }
    }
}
