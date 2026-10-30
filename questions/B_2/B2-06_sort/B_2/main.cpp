#include <iostream>
#include <string>

#include "List.h"

using namespace std;

int main() {
    List<int> numbers;
    numbers.prepend(-1);
    numbers.prepend(6);
    numbers.prepend(3);
    numbers.prepend(5);
    numbers.prepend(0);
    cout << numbers << " (size " << numbers.getSize() << ")" << endl;
    numbers.sort();
    cout << numbers << " (size " << numbers.getSize() << ")" << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
0->5->3->6->-1 (size 5)
-1->0->3->5->6 (size 5)
*/
