#include <iostream>

#include "Binary.h"

using namespace std;

int main() {
    Binary a("01");
    Binary b("1101");
    cout << "a: " << a << ", b: " << b << endl;

    a = b;
    cout << "after a = b, a: " << a << " (size " << a.getSize() << ")" << endl;

    b[0] = false;
    cout << "after b[0] = false, b: " << b << ", a: " << a << endl;

    a = a;
    cout << "after a = a, a: " << a << endl;

    Binary c("000");
    a = b = c;
    cout << "after a = b = c, a: " << a << ", b: " << b << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
a: 01, b: 1101
after a = b, a: 1101 (size 4)
after b[0] = false, b: 0101, a: 1101
after a = a, a: 1101
after a = b = c, a: 000, b: 000
*/
