#include <iostream>

#include "List.h"

using namespace std;

int main() {
    List<int> list;
    list.prepend(15);
    list.prepend(10);
    list.prepend(5);
    cout << list << endl;
    cout << boolalpha;

    cout << "Contains 10: " << list.contains(list.head(), 10) << endl;
    cout << "Contains 7: " << list.contains(list.head(), 7) << endl;
    cout << "Contains 15 (the last node): " << list.contains(list.head(), 15) << endl;
    cout << "Contains 5, from the second node: " << list.contains(list.head()->next(), 5) << endl;

    List<int> empty;
    cout << "Empty list contains 5: " << empty.contains(empty.head(), 5) << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
5->10->15
Contains 10: true
Contains 7: false
Contains 15 (the last node): true
Contains 5, from the second node: false
Empty list contains 5: false
*/
