#include "Menu.h"

Menu::Menu(int maxSize) : maxSize(maxSize) {
    items = new Item*[maxSize];
    for (int i = 0; i < maxSize; i++) {
        items[i] = NULL;
    }
}

Menu::~Menu() {
    for (int i = 0; i < maxSize; i++) {
        delete items[i];
    }
    delete[] items;
}

// The menu owns every item given to it. The item goes in the first empty (NULL) slot.
// If the menu is full, the item is deleted and the menu does not change.
Menu& Menu::operator+(Item* item) {
    for (int i = 0; i < maxSize; i++) {
        if (items[i] == NULL) {
            items[i] = item;
            return *this;
        }
    }
    delete item;
    return *this;
}

ostream& operator<<(ostream& out, const Menu& menu) {
    out << "Menu (max " << menu.maxSize << "):" << endl;
    for (int i = 0; i < menu.maxSize; i++) {
        out << "  [" << i << "] ";
        if (menu.items[i] == NULL) {
            out << "empty";
        } else {
            out << *menu.items[i];
        }
        out << endl;
    }
    return out;
}
