#include <iostream>
#include <string>

#include "List.h"

using namespace std;

template <class T>
void tryIndex(List<T>& list, int index) {
    try {
        T value = list[index];
        cout << "list[" << index << "]: " << value << endl;
    } catch (Exception& e) {
        cout << "list[" << index << "]: Caught: " << e.what() << endl;
    }
}

int main() {
    List<int> numbers;
    numbers.prepend(30);
    numbers.prepend(20);
    numbers.prepend(10);
    cout << numbers << endl;
    tryIndex(numbers, 0);
    tryIndex(numbers, 2);
    tryIndex(numbers, 1);
    tryIndex(numbers, 3);
    tryIndex(numbers, -1);
    return 0;
}
/*
ExpectedOutput:
*/
/*
10->20->30
list[0]: 10
list[2]: 30
list[1]: 20
list[3]: Caught: Index out of bounds
list[-1]: Caught: Index out of bounds
*/
