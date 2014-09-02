#ifndef _HTTP_HEADER_PARSER_H_
#define _HTTP_HEADER_PARSER_H_

class HTTPHeaderParser {
    public:
        HTTPHeaderParser(int fd);
        ~HTTPHeaderParser();

        int length(void);
        int num(void);
    private:
        void parser(void);
        void readLine(char *buf, int size);
    private:
        int mFd;
        int mLength;
        int mInit;
        int mNum;
};

#endif //_HTTP_HEADER_PARSER_H_

