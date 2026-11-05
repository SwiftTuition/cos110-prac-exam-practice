#include <iostream>
#include <string>

#include "Binary.h"
#include "Templates.h"

using namespace std;

int main() {
    cout << addition(3, 4.5) << endl;
    cout << addition(2.5, 3) << endl;
    cout << addition(string("10"), string("01")) << endl;

    Binary a("0101");
    Binary b("0011");
    try {
        Binary sum = addition(a, b);
        cout << sum << endl;
    } catch (const char* msg) {
        cout << "Caught: " << msg << endl;
    }
    cout << "a and b are unchanged: " << a << " " << b << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
7
5.5
1001
Caught: Cannot add two binary strings
a and b are unchanged: 0101 0011
*/
