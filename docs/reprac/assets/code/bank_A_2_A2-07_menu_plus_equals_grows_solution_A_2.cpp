#include "Menu.h"

Menu& Menu::operator+=(Item* item) {
    // Use a free slot if there is one.
    for (int i = 0; i < maxSize; i++) {
        if (items[i] == NULL) {
            items[i] = item;
            return *this;
        }
    }
    // The menu is full: make an array with one more slot.
    Item** bigger = new Item*[maxSize + 1];
    for (int i = 0; i < maxSize; i++) {
        bigger[i] = items[i];
    }
    bigger[maxSize] = item;
    // Delete the old array of pointers only. The items now belong to the new array.
    delete[] items;
    items = bigger;
    maxSize++;
    return *this;
}
