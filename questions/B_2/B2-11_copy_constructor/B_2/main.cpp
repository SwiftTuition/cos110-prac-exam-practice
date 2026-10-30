#include <iostream>
#include <string>

#include "List.h"

using namespace std;

template <class T>
void show(List<T>& list) {
    cout << list << " (size " << list.getSize() << ")" << endl;
}

int main() {
    List<int> original;
    original.prepend(3);
    original.prepend(2);
    original.prepend(1);
    List<int> copy(original);
    cout << "original: ";
    show(original);
    cout << "copy:     ";
    show(copy);
    original.prepend(0);
    copy.prepend(9);
    cout << "original: ";
    show(original);
    cout << "copy:     ";
    show(copy);
    return 0;
}
/*
ExpectedOutput:
*/
/*
original: 1->2->3 (size 3)
copy:     1->2->3 (size 3)
original: 0->1->2->3 (size 4)
copy:     9->1->2->3 (size 4)
*/
