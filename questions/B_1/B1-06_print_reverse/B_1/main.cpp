#include <iostream>

#include "List.h"

using namespace std;

int main() {
    List<int> list;
    list.prepend(3);
    list.prepend(2);
    list.prepend(1);
    cout << list << endl;

    cout << "Reverse:" << endl;
    list.printReverse(list.head());

    cout << "Reverse from the second node:" << endl;
    list.printReverse(list.head()->next());

    List<int> empty;
    cout << "Reverse of an empty list:" << endl;
    empty.printReverse(empty.head());
    cout << "(end)" << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
1->2->3
Reverse:
3
2
1
Reverse from the second node:
3
2
Reverse of an empty list:
(end)
*/
