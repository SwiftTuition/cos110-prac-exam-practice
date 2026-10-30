
#include <iostream>
#include <string>

#include "List.h"

using namespace std;

int main() {
    List<int> numbers;
    cout << numbers << endl;
    numbers.prepend(3);
    numbers.prepend(2);
    numbers.prepend(1);
    cout << numbers << endl;

    List<string> names;
    names.prepend("Sipho");
    names.prepend("Thandi");
    cout << names << " (size " << names.getSize() << ")" << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Empty List
1->2->3
Thandi->Sipho (size 2)
*/
