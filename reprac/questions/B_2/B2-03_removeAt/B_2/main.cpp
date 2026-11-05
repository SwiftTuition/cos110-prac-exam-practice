#include <iostream>

#include "Binary.h"
#include "BinaryStrings.h"
#include "Node.h"

using namespace std;

void tryRemove(BinaryStrings& list, int pos) {
    bool removed = list.removeAt(pos);
    cout << "removeAt(" << pos << "): " << (removed ? "true " : "false") << "  " << list
         << " (size " << list.getSize() << ")" << endl;
}

int main() {
    BinaryStrings list;
    list.prepend(Binary("0101"));
    list.prepend(Binary("1101"));
    list.prepend(Binary("0011"));
    list.prepend(Binary("000"));
    list.prepend(Binary("1"));
    cout << list << " (size " << list.getSize() << ")" << endl;

    tryRemove(list, 2);
    tryRemove(list, 0);
    tryRemove(list, 2);
    tryRemove(list, 5);
    tryRemove(list, -1);
    tryRemove(list, 1);
    tryRemove(list, 0);
    tryRemove(list, 0);
    return 0;
}
/*
ExpectedOutput:
*/
/*
1 -> 000 -> 0011 -> 1101 -> 0101 (size 5)
removeAt(2): true   1 -> 000 -> 1101 -> 0101 (size 4)
removeAt(0): true   000 -> 1101 -> 0101 (size 3)
removeAt(2): true   000 -> 1101 (size 2)
removeAt(5): false  000 -> 1101 (size 2)
removeAt(-1): false  000 -> 1101 (size 2)
removeAt(1): true   000 (size 1)
removeAt(0): true   Empty (size 0)
removeAt(0): false  Empty (size 0)
*/
