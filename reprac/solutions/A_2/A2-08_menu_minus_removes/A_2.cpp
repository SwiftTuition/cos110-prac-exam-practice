#include "Menu.h"

Menu& Menu::operator-(string name) {
    for (int i = 0; i < maxSize; i++) {
        if (items[i] != NULL && items[i]->getName() == name) {
            delete items[i];
            // Move every later pointer one slot to the front.
            for (int j = i; j < maxSize - 1; j++) {
                items[j] = items[j + 1];
            }
            // The last slot now has no item of its own.
            items[maxSize - 1] = NULL;
            return *this;
        }
    }
    // No item has this name: the menu does not change.
    return *this;
}
