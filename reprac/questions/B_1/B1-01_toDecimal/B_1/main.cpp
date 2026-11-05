#include <iostream>

#include "Binary.h"

using namespace std;

int main() {
    Binary a("1011");
    cout << a << " up to index 3: " << a.toDecimal(3) << endl;
    cout << a << " up to index 1: " << a.toDecimal(1) << endl;
    cout << a << " up to index 0: " << a.toDecimal(0) << endl;

    Binary b("00000101");
    cout << b << " whole string: " << b.toDecimal(b.getSize() - 1) << endl;

    cout << "invalid index 4: " << a.toDecimal(4) << endl;
    cout << "invalid index -1: " << a.toDecimal(-1) << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
1011 up to index 3: 11
1011 up to index 1: 2
1011 up to index 0: 1
00000101 whole string: 5
invalid index 4: 0
invalid index -1: 0
*/
