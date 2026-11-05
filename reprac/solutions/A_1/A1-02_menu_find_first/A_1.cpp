#include "Menu.h"

Item Menu::findFirst(string type) {
    // Check the type name before the loop. An invalid name throws even for an empty menu.
    char code;
    if (type == "Starter") {
        code = 'S';
    } else if (type == "Main") {
        code = 'M';
    } else if (type == "Dessert") {
        code = 'D';
    } else {
        throw InvalidType(type);
    }
    for (int i = 0; i < maxSize; i++) {
        if (items[i] != NULL && items[i]->getType() == code) {
            return *items[i];
        }
    }
    // The loop ended, so no item of this type is on the menu.
    if (code == 'S') {
        throw StarterNotFound();
    }
    if (code == 'M') {
        throw MainNotFound();
    }
    throw DessertNotFound();
}
