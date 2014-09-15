#include <iostream>
#include "http_download.h"
#include "http_send_request.h"

using namespace std;

static void url_download(const char *url)
{
    http_url_parser url_parser(url);
    cout << url_parser.port() << " " << url_parser.host() << " " 
        << url_parser.host_ip() << " " << url_parser.path() << endl;

    HTTPDownLoader downloader(url_parser.port(), url_parser.host(), url_parser.path());
    downloader.download();
}

static void send_request_to_server(const char *url)
{
    http_send_request send_request(url);
    send_request.send_request("OPTIONS");
    send_request.dump_response();
}

void show_usage(void)
{
    printf("Usage:\n"
            "\t -d file_download_url  # download file.\n"
            "\t -r request            # send request.\n\n");
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        show_usage();
    } else if (! strcmp(argv[1], "-d")) {
        url_download(argv[2]);
    } else if (! strcmp(argv[1], "-r")) {
        send_request_to_server(argv[2]);
    } else {
        show_usage();
    }

    return 0;
}

