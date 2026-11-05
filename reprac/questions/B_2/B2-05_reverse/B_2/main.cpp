#include <iostream>

#include "Binary.h"
#include "BinaryStrings.h"
#include "Node.h"

using namespace std;

int main() {
    BinaryStrings list;
    list.prepend(Binary("0101"));
    list.prepend(Binary("1101"));
    list.prepend(Binary("0011"));
    list.prepend(Binary("000"));
    cout << list << " (size " << list.getSize() << ")" << endl;

    list.reverse();
    cout << list << " (size " << list.getSize() << ")" << endl;

    list.reverse();
    cout << list << " (size " << list.getSize() << ")" << endl;

    BinaryStrings empty;
    empty.reverse();
    cout << empty << " (size " << empty.getSize() << ")" << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
000 -> 0011 -> 1101 -> 0101 (size 4)
0101 -> 1101 -> 0011 -> 000 (size 4)
000 -> 0011 -> 1101 -> 0101 (size 4)
Empty (size 0)
*/
