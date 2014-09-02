#include <iostream>

using namespace std;

//void print_str(char *str)
void print_str(const char *str)
{
    cout << str << endl;
}

int main(int argc, char *argv[])
{
    print_str("hello");
    return 0;
}

