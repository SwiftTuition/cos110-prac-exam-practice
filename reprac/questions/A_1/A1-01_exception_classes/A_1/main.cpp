
#include <iostream>

#include "Exception.h"

using namespace std;

void throwOne(int which) {
    if (which == 0) {
        throw InvalidType("Drink");
    }
    if (which == 1) {
        throw NothingMatchingFilter("Dessert");
    }
    if (which == 2) {
        throw NothingAboveMinimumValue();
    }
    if (which == 3) {
        throw NothingBelowMaximumValue();
    }
    if (which == 4) {
        throw StarterNotFound();
    }
    if (which == 5) {
        throw MainNotFound();
    }
    throw DessertNotFound();
}

int main() {
    Exception plain("Kitchen closed");
    plain.printException();
    cout << plain << endl;

    for (int which = 0; which <= 6; which++) {
        try {
            throwOne(which);
        } catch (NothingMatchingFilter& e) {
            cout << "Filter: ";
            e.printException();
        } catch (NotFoundException& e) {
            cout << "Not found: ";
            e.printException();
        } catch (Exception& e) {
            cout << "Other: ";
            e.printException();
        }
    }
    return 0;
}
/*
ExpectedOutput:
*/
/*
Exception: Kitchen closed
Exception: Kitchen closed
Other: Exception: Invalid type: Drink
Filter: Exception: Nothing matching filter: Dessert
Filter: Exception: Nothing matching filter: above minimum value
Filter: Exception: Nothing matching filter: below maximum value
Not found: Exception: Item not found
Not found: Exception: Item not found
Not found: Exception: Item not found
*/
