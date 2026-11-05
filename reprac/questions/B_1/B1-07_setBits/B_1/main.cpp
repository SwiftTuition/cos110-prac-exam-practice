#include <iostream>

#include "Binary.h"

using namespace std;

int main() {
    Binary a("1011");
    cout << "a: " << a << " (size " << a.getSize() << ")" << endl;

    Binary b("0000");
    b.setBits("11", 0);
    cout << "after setBits(\"11\", 0): " << b << endl;
    b.setBits("0110", 2);
    cout << "after setBits(\"0110\", 2): " << b << endl;
    b.setBits("111111", 0);
    cout << "after setBits(\"111111\", 0): " << b << endl;
    b.setBits("0000", -1);
    cout << "after setBits(\"0000\", -1): " << b << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
a: 1011 (size 4)
after setBits("11", 0): 1100
after setBits("0110", 2): 1110
after setBits("111111", 0): 1111
after setBits("0000", -1): 1111
*/
