#include <iostream>
#include <string>

#include "List.h"

using namespace std;

template <class T>
void show(string label, List<T>& list) {
    cout << label << list << " (size " << list.getSize() << ")" << endl;
}

int main() {
    List<int> a;
    a.prepend(9);

    List<int> b;
    b.prepend(3);
    b.prepend(2);
    b.prepend(1);

    show("a: ", a);
    show("b: ", b);

    a = b;
    show("a after a = b: ", a);

    b.prepend(0);
    show("b after b.prepend(0): ", b);
    show("a has not changed: ", a);
    return 0;
}
/*
ExpectedOutput:
*/
/*
a: 9 (size 1)
b: 1->2->3 (size 3)
a after a = b: 1->2->3 (size 3)
b after b.prepend(0): 0->1->2->3 (size 4)
a has not changed: 1->2->3 (size 3)
*/
