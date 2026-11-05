#include "Menu.h"

Menu& Menu::operator=(const Menu& other) {
    if (this == &other) {
        return *this;
    }

    // Empty this menu. The array stays: its size (maxSize) does not change.
    for (int i = 0; i < maxSize; i++) {
        delete items[i];
        items[i] = NULL;
    }

    // Copy slot i of other into slot i of this menu, for every slot that both menus have.
    for (int i = 0; i < maxSize && i < other.maxSize; i++) {
        if (other.items[i] != NULL) {
            items[i] = new Item(*other.items[i]);
        }
    }

    return *this;
}
