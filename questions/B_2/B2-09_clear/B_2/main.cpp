#include <iostream>
#include <string>

#include "List.h"

using namespace std;

template <class T>
void show(List<T>& list) {
    cout << list << " (size " << list.getSize() << ")" << endl;
}

int main() {
    List<int> numbers;
    for (int i = 4; i >= 1; i--) {
        numbers.prepend(i);
    }
    show(numbers);
    numbers.clear();
    show(numbers);
    numbers.prepend(7);
    numbers.prepend(8);
    show(numbers);
    return 0;
}
/*
ExpectedOutput:
*/
/*
1->2->3->4 (size 4)
Empty List (size 0)
8->7 (size 2)
*/
