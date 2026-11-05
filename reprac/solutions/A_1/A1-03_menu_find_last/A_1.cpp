#include "Menu.h"

Item Menu::findLast(string type) {
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
    // Start at the last slot and move to the front. The first match found is the last item.
    for (int i = maxSize - 1; i >= 0; i--) {
        if (items[i] != NULL && items[i]->getType() == code) {
            return *items[i];
        }
    }
    if (code == 'S') {
        throw StarterNotFound();
    }
    if (code == 'M') {
        throw MainNotFound();
    }
    throw DessertNotFound();
}
