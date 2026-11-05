
#include <iostream>

#include "Exception.h"

using namespace std;

int main() {
    Exception plain("Kitchen closed");
    cout << plain << endl;

    InvalidType bad("Drink");
    cout << bad << " (InvalidType)" << endl;

    try {
        throw NothingBelowMaximumValue();
    } catch (Exception& e) {
        cout << "Caught: " << e << endl;
    }
    try {
        throw DessertNotFound();
    } catch (NotFoundException& e) {
        cout << "Caught: " << e << endl;
    }

    const Exception& ref = bad;
    cout << ref << "!" << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Exception: Kitchen closed
Exception: Invalid type: Drink (InvalidType)
Caught: Exception: Nothing matching filter: below maximum value
Caught: Exception: Item not found
Exception: Invalid type: Drink!
*/
