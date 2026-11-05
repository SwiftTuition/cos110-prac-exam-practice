#include <iostream>

#include "Binary.h"
#include "BinaryStrings.h"
#include "Node.h"

using namespace std;

int main() {
    BinaryStrings list;
    list.prepend(Binary("1101"));
    list.prepend(Binary("0011"));
    list.prepend(Binary("000"));
    cout << list << " (size " << list.getSize() << ")" << endl;

    list.insertAt(Binary("1"), 0);
    cout << "insertAt(1, 0):   " << list << " (size " << list.getSize() << ")" << endl;

    list.insertAt(Binary("01"), 2);
    cout << "insertAt(01, 2):  " << list << " (size " << list.getSize() << ")" << endl;

    list.insertAt(Binary("111"), 99);
    cout << "insertAt(111, 99): " << list << " (size " << list.getSize() << ")" << endl;

    list.insertAt(Binary("10"), -3);
    cout << "insertAt(10, -3): " << list << " (size " << list.getSize() << ")" << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
000 -> 0011 -> 1101 (size 3)
insertAt(1, 0):   1 -> 000 -> 0011 -> 1101 (size 4)
insertAt(01, 2):  1 -> 000 -> 01 -> 0011 -> 1101 (size 5)
insertAt(111, 99): 1 -> 000 -> 01 -> 0011 -> 1101 -> 111 (size 6)
insertAt(10, -3): 10 -> 1 -> 000 -> 01 -> 0011 -> 1101 -> 111 (size 7)
*/
