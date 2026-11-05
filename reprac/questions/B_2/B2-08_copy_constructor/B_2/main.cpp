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

    BinaryStrings copy(list);
    cout << "list: " << list << " (size " << list.getSize() << ")" << endl;
    cout << "copy: " << copy << " (size " << copy.getSize() << ")" << endl;

    copy.getHead()->getData()[0] = true;
    copy.prepend(Binary("1"));
    cout << "after changing the copy:" << endl;
    cout << "list: " << list << " (size " << list.getSize() << ")" << endl;
    cout << "copy: " << copy << " (size " << copy.getSize() << ")" << endl;

    BinaryStrings empty;
    BinaryStrings emptyCopy(empty);
    cout << "copy of an empty list: " << emptyCopy << " (size " << emptyCopy.getSize() << ")" << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
list: 000 -> 0011 -> 1101 (size 3)
copy: 000 -> 0011 -> 1101 (size 3)
after changing the copy:
list: 000 -> 0011 -> 1101 (size 3)
copy: 1 -> 100 -> 0011 -> 1101 (size 4)
copy of an empty list: Empty (size 0)
*/
