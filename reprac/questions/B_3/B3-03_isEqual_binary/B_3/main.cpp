#include <iostream>
#include <string>

#include "Binary.h"
#include "Templates.h"

using namespace std;

void show(const Binary& a, const Binary& b) {
    cout << a << " and " << b << ": " << (isEqual(a, b) ? "equal" : "not equal") << endl;
}

int main() {
    cout << "3 and 3: " << (isEqual(3, 3) ? "equal" : "not equal") << endl;
    cout << "on and off: " << (isEqual(string("on"), string("off")) ? "equal" : "not equal") << endl;

    show(Binary("0101"), Binary("0101"));
    show(Binary("0101"), Binary("0100"));
    show(Binary("011"), Binary("11"));
    show(Binary("11"), Binary("011"));
    return 0;
}
/*
ExpectedOutput:
*/
/*
3 and 3: equal
on and off: not equal
0101 and 0101: equal
0101 and 0100: not equal
011 and 11: not equal
11 and 011: not equal
*/
