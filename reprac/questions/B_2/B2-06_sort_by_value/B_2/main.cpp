#include <iostream>

#include "Binary.h"
#include "BinaryStrings.h"
#include "Node.h"

using namespace std;

int main() {
    BinaryStrings list;
    list.prepend(Binary("0"));
    list.prepend(Binary("011"));
    list.prepend(Binary("1000"));
    list.prepend(Binary("11"));
    list.prepend(Binary("0101"));
    cout << list << " (size " << list.getSize() << ")" << endl;

    list.sort();
    cout << list << " (size " << list.getSize() << ")" << endl;

    BinaryStrings empty;
    empty.sort();
    cout << empty << " (size " << empty.getSize() << ")" << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
0101 -> 11 -> 1000 -> 011 -> 0 (size 5)
0 -> 11 -> 011 -> 0101 -> 1000 (size 5)
Empty (size 0)
*/
