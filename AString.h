#ifndef _A_STRING_H_
#define _A_STRING_H_

class AString {
    public:
        AString();
        AString(char *);
        ~AString();

        void append(char *_s);
        char *c_str(void);
    private:
        char *str;
};

#endif //_A_STRING_H_

