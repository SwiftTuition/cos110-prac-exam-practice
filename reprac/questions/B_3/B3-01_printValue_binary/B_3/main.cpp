#include <iostream>
#include <string>

#include "Binary.h"
#include "Templates.h"

using namespace std;

int main() {
    printValue(5);
    printValue(2.5);
    printValue(string("embedded"));
    printValue('c');

    Binary a("0101");
    printValue(a);
    printValue(Binary("11111111"));
    return 0;
}
/*
ExpectedOutput:
*/
/*
Value: 5
Value: 2.5
Value: embedded
Value: c
Binary: 0101 (5)
Binary: 11111111 (255)
*/
