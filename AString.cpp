#include <string.h>
#include <stdlib.h>

#include "AString.h"

AString::AString(void)
{
    str = (char *)malloc(1);
    str[0] = 0;
}

AString::AString(char * _str) 
{
    this->append(_str);
}

AString::~AString()
{
    free(str);
}

void AString::append(char *_str)
{
    str = (char *)realloc(str, strlen(str) + strlen(_str) + 1);

    strcat(str, _str);
}

char * AString::c_str(void)
{
    return str;
}
