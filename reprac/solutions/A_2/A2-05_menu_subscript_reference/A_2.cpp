#include "Menu.h"

Item*& Menu::operator[](int index) {
    // Return the slot itself (a reference to the pointer in the array), not a copy of it.
    return items[index];
}
