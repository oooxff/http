#ifndef _HTTP_HEADER_PARSER_H_
#define _HTTP_HEADER_PARSER_H_

class HTTPHeaderParser {
    public:
        HTTPHeaderParser(int fd);
        ~HTTPHeaderParser();

        int length(void);
    private:
        void parser(void);
        char *get_line(char *buf, int size);
    private:
        int mFd;
        int mLength;
        int mInit;
};

#endif //_HTTP_HEADER_PARSER_H_

