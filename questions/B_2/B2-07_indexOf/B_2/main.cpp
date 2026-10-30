#include <iostream>
#include <string>

#include "List.h"

using namespace std;

template <class T>
void find(List<T>& list, T value) {
    cout << "indexOf(" << value << "): " << list.indexOf(value) << endl;
}

int main() {
    List<string> departments;
    departments.prepend("Development");
    departments.prepend("HR");
    departments.prepend("Marketing");
    departments.prepend("Sales");
    cout << departments << endl;
    find(departments, string("Sales"));
    find(departments, string("HR"));
    find(departments, string("Development"));
    find(departments, string("Finance"));
    return 0;
}
/*
ExpectedOutput:
*/
/*
Sales->Marketing->HR->Development
indexOf(Sales): 0
indexOf(HR): 2
indexOf(Development): 3
indexOf(Finance): -1
*/
