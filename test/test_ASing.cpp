#include "AString.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    AString s1;

    cout << "1: " << s1.c_str() << endl;
    s1.append("hello world");
    cout << "2: " << s1.c_str() << endl;
    s1.append(".");
    cout << "3: " << s1.c_str() << endl;
    s1.append(" This is only a test text.");
    cout << "4: " << s1.c_str() << endl;
    s1.append("This is a long long long long long long long long long long long long long long text.");
    cout << "4: " << s1.c_str() << endl;

    return 0;
}

