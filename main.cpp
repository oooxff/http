#include <iostream>
#include "http_download.h"
#include "http_send_request.h"

using namespace std;

static void url_download(const char *url)
{
    http_url_parser url_parser(url);
    cout << url_parser.port() << " " << url_parser.host() << " " << url_parser.path() << endl;
    HTTPDownLoader downloader(url_parser.port(), url_parser.host(), url_parser.path());
    downloader.download();
}

static void send_request_to_server(const char *url)
{
    http_send_request send_request(url);
    send_request.send_request("OPTIONS");
    send_request.dump_response();
}

int main(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i ++) {
        send_request_to_server(argv[i]);
    }

    return 0;
}

