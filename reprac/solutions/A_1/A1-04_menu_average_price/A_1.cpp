#include "Menu.h"

float Menu::averagePrice(string type) {
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
    float total = 0;
    int count = 0;
    for (int i = 0; i < maxSize; i++) {
        if (items[i] != NULL && items[i]->getType() == code) {
            total += items[i]->getPrice();
            count++;
        }
    }
    // Throw before the division, so the function never divides by 0.
    if (count == 0) {
        throw NothingMatchingFilter(type);
    }
    return total / count;
}
