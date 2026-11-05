#include <iostream>

#include "Binary.h"
#include "BinaryStrings.h"
#include "Node.h"

using namespace std;

void tryRemove(BinaryStrings& list, string bits) {
    bool removed = list.remove(Binary(bits));
    cout << "remove(" << bits << "): " << (removed ? "true " : "false") << "  " << list
         << " (size " << list.getSize() << ")" << endl;
}

int main() {
    BinaryStrings list;
    list.prepend(Binary("0011"));
    list.prepend(Binary("101"));
    list.prepend(Binary("0011"));
    list.prepend(Binary("0101"));
    cout << list << " (size " << list.getSize() << ")" << endl;

    tryRemove(list, "0011");
    tryRemove(list, "11");
    tryRemove(list, "101");
    tryRemove(list, "0101");
    tryRemove(list, "0011");
    tryRemove(list, "0011");
    return 0;
}
/*
ExpectedOutput:
*/
/*
0101 -> 0011 -> 101 -> 0011 (size 4)
remove(0011): true   0101 -> 101 -> 0011 (size 3)
remove(11): false  0101 -> 101 -> 0011 (size 3)
remove(101): true   0101 -> 0011 (size 2)
remove(0101): true   0011 (size 1)
remove(0011): true   Empty (size 0)
remove(0011): false  Empty (size 0)
*/
