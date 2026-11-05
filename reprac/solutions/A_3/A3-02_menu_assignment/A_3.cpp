#include "Menu.h"

Menu& Menu::operator=(const Menu& other) {
    if (this == &other) {
        return *this;
    }

    for (int i = 0; i < maxSize; i++) {
        delete items[i];
    }
    delete[] items;

    maxSize = other.maxSize;
    items = new Item*[maxSize];
    for (int i = 0; i < maxSize; i++) {
        if (other.items[i] == NULL) {
            items[i] = NULL;
        } else {
            items[i] = new Item(*other.items[i]);
        }
    }

    return *this;
}
