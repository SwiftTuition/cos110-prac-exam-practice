#include <iostream>

#include "Binary.h"
#include "BinaryStrings.h"
#include "Node.h"

using namespace std;

int main() {
    BinaryStrings list;
    cout << list << " (size " << list.getSize() << ")" << endl;

    list.append(Binary("0101"));
    cout << list << " (size " << list.getSize() << ")" << endl;

    list.append(Binary("11"));
    list.prepend(Binary("000"));
    list.append(Binary("1"));
    cout << list << " (size " << list.getSize() << ")" << endl;

    Binary x("0000");
    list.append(x);
    x[0] = true;
    cout << list << " (size " << list.getSize() << ")" << endl;
    cout << "x is now " << x << "; the list keeps its own copy" << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Empty (size 0)
0101 (size 1)
000 -> 0101 -> 11 -> 1 (size 4)
000 -> 0101 -> 11 -> 1 -> 0000 (size 5)
x is now 1000; the list keeps its own copy
*/
