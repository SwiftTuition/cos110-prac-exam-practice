#include <iostream>

#include "Binary.h"
#include "BinaryStrings.h"
#include "Node.h"

using namespace std;

int main() {
    BinaryStrings list;
    cout << list << ": " << list.calculatePos() << " positive" << endl;

    list.prepend(Binary("0101"));
    list.prepend(Binary("1101"));
    list.prepend(Binary("0011"));
    list.prepend(Binary("000"));
    cout << list << ": " << list.calculatePos() << " positive" << endl;

    list.getHead()->getData()[2] = true;
    cout << list << ": " << list.calculatePos() << " positive" << endl;

    list.getHead()->next()->next()->getData()[0] = false;
    cout << list << ": " << list.calculatePos() << " positive" << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Empty: 0 positive
000 -> 0011 -> 1101 -> 0101: 2 positive
001 -> 0011 -> 1101 -> 0101: 3 positive
001 -> 0011 -> 0101 -> 0101: 4 positive
*/
