#include "Menu.h"

Menu::Menu(const Menu& other) {
    maxSize = other.maxSize;
    items = new Item*[maxSize];
    for (int i = 0; i < maxSize; i++) {
        if (other.items[i] == NULL) {
            items[i] = NULL;
        } else {
            items[i] = new Item(*other.items[i]);
        }
    }
}
