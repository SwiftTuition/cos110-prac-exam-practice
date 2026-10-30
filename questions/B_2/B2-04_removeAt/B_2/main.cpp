#include <iostream>
#include <string>

#include "List.h"

using namespace std;

template <class T>
void tryRemoveAt(List<T>& list, int pos) {
    bool removed = list.removeAt(pos);
    cout << "removeAt(" << pos << "): " << (removed ? "true" : "false");
    cout << " -> " << list << " (size " << list.getSize() << ")" << endl;
}

int main() {
    List<int> numbers;
    for (int i = 50; i >= 10; i -= 10) {
        numbers.prepend(i);
    }
    cout << numbers << " (size " << numbers.getSize() << ")" << endl;
    tryRemoveAt(numbers, 2);
    tryRemoveAt(numbers, 0);
    tryRemoveAt(numbers, 2);
    tryRemoveAt(numbers, 5);
    tryRemoveAt(numbers, -1);
    return 0;
}
/*
ExpectedOutput:
*/
/*
10->20->30->40->50 (size 5)
removeAt(2): true -> 10->20->40->50 (size 4)
removeAt(0): true -> 20->40->50 (size 3)
removeAt(2): true -> 20->40 (size 2)
removeAt(5): false -> 20->40 (size 2)
removeAt(-1): false -> 20->40 (size 2)
*/
