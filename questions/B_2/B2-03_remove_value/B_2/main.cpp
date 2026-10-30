#include <iostream>
#include <string>

#include "List.h"

using namespace std;

template <class T>
void tryRemove(List<T>& list, T value) {
    bool removed = list.remove(value);
    cout << "remove(" << value << "): " << (removed ? "true" : "false");
    cout << " -> " << list << " (size " << list.getSize() << ")" << endl;
}

int main() {
    List<int> numbers;
    for (int i = 5; i >= 1; i--) {
        numbers.prepend(i);
    }
    cout << numbers << " (size " << numbers.getSize() << ")" << endl;
    tryRemove(numbers, 3);
    tryRemove(numbers, 1);
    tryRemove(numbers, 5);
    tryRemove(numbers, 9);
    return 0;
}
/*
ExpectedOutput:
*/
/*
1->2->3->4->5 (size 5)
remove(3): true -> 1->2->4->5 (size 4)
remove(1): true -> 2->4->5 (size 3)
remove(5): true -> 2->4 (size 2)
remove(9): false -> 2->4 (size 2)
*/
