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
    for (int i = 5; i >= 1; i--) {
        numbers.prepend(i);
    }
    show(numbers);
    numbers.reverse();
    show(numbers);
    numbers.reverse();
    show(numbers);
    return 0;
}
/*
ExpectedOutput:
*/
/*
1->2->3->4->5 (size 5)
5->4->3->2->1 (size 5)
1->2->3->4->5 (size 5)
*/
