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
    cout << list << endl;

    cout << "Reverse:" << endl;
    list.printReverse(list.getHead());

    cout << "Reverse from the second node:" << endl;
    list.printReverse(list.getHead()->next());

    BinaryStrings empty;
    cout << "Reverse of an empty list:" << endl;
    empty.printReverse(empty.getHead());
    cout << "(end)" << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
000 -> 0011 -> 1101 -> 0101
Reverse:
0101
1101
0011
000
Reverse from the second node:
0101
1101
0011
Reverse of an empty list:
(end)
*/
