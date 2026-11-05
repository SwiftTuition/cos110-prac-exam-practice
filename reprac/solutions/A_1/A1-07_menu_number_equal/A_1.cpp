#include "Menu.h"

int Menu::numberEqual(string type, float value) {
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
    int count = 0;
    for (int i = 0; i < maxSize; i++) {
        // The NULL check comes first: && stops at the first false part.
        if (items[i] != NULL && items[i]->getType() == code && items[i]->getPrice() == value) {
            count++;
        }
    }
    // No item has this price. The message names the type.
    if (count == 0) {
        throw NothingMatchingFilter(type);
    }
    return count;
}
