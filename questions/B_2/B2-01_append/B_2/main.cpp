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
    show(numbers);
    numbers.append(10);
    show(numbers);
    numbers.append(20);
    numbers.append(30);
    show(numbers);
    numbers.prepend(5);
    numbers.append(40);
    show(numbers);
    return 0;
}
/*
ExpectedOutput:
*/
/*
Empty List (size 0)
10 (size 1)
10->20->30 (size 3)
5->10->20->30->40 (size 5)
*/
