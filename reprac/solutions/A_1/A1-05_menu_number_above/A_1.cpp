#include "Menu.h"

int Menu::numberAbove(string type, float value) {
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
        if (items[i] != NULL && items[i]->getType() == code && items[i]->getPrice() > value) {
            count++;
        }
    }
    // No item is above the value.
    if (count == 0) {
        throw NothingAboveMinimumValue();
    }
    return count;
}
