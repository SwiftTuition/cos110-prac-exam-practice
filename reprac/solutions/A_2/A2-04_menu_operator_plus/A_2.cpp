#include "Menu.h"

Menu& Menu::operator+(Item* item) {
    for (int i = 0; i < maxSize; i++) {
        if (items[i] == NULL) {
            items[i] = item;
            // Stop at the first empty slot; the item must be stored only once.
            return *this;
        }
    }
    // The menu is full. The menu owns the item, so it must delete it.
    delete item;
    return *this;
}
