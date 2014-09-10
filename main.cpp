#include <iostream>
#include "http_download.h"

using namespace std;

static void url_download(const char *url)
{
    http_url_parser url_parser(url);
    cout << url_parser.port() << " " << url_parser.host() << " " << url_parser.path() << endl;
    HTTPDownLoader downloader(url_parser.port(), url_parser.host(), url_parser.path());
    downloader.download();
}

int main(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i ++) {
        url_download(argv[i]);
    }

    return 0;
}

