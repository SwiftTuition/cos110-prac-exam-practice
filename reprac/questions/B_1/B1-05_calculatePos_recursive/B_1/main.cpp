#include <iostream>

#include "Binary.h"
#include "BinaryStrings.h"
#include "Node.h"

using namespace std;

int main() {
    BinaryStrings list;
    cout << list << ": " << list.calculatePos(list.getHead(), 1) << " positive" << endl;

    list.prepend(Binary("0101"));
    list.prepend(Binary("1101"));
    list.prepend(Binary("0011"));
    list.prepend(Binary("000"));
    cout << list << ": " << list.calculatePos(list.getHead(), 1) << " positive" << endl;

    Node<Binary>* third = list.getHead()->next()->next();
    cout << "from " << third->getData() << ": " << list.calculatePos(third, 1) << " positive" << endl;

    cout << "invalid index 0: " << list.calculatePos(list.getHead(), 0) << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Empty: 0 positive
000 -> 0011 -> 1101 -> 0101: 2 positive
from 1101: 1 positive
invalid index 0: 0
*/
