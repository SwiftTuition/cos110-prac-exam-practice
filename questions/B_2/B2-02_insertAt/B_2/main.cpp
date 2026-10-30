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
    numbers.insertAt(20, 0);
    show(numbers);
    numbers.insertAt(40, 5);
    show(numbers);
    numbers.insertAt(30, 1);
    show(numbers);
    numbers.insertAt(10, -3);
    show(numbers);
    numbers.insertAt(35, 3);
    show(numbers);
    numbers.insertAt(50, 5);
    show(numbers);
    return 0;
}
/*
ExpectedOutput:
*/
/*
20 (size 1)
20->40 (size 2)
20->30->40 (size 3)
10->20->30->40 (size 4)
10->20->30->35->40 (size 5)
10->20->30->35->40->50 (size 6)
*/
