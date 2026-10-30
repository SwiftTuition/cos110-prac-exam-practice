#include "Templates.h"

// For a Department pointer, print the Department it points to, not the address.
template <>
void printItem<Department*>(Department* const& item) {
    if (item == NULL) {
        cout << "No department" << endl;
        return;
    }
    cout << *item;    // Department's operator<< already ends its lines
}
