SRC = \
	AString.cpp  http_download.cpp  http_header_parser.cpp  http_send_request.cpp  http_url_parser.cpp  main.cpp Socket.cpp

all :
	g++ ${SRC} -g -Wall -o app
clean:
	rm -rf app.dSYM app
