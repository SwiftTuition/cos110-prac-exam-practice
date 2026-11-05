#include "Menu.h"

// "Starter" -> 'S', "Main" -> 'M', "Dessert" -> 'D'. Any other string throws InvalidType.
static char typeCode(string type) {
    if (type == "Starter") {
        return 'S';
    }
    if (type == "Main") {
        return 'M';
    }
    if (type == "Dessert") {
        return 'D';
    }
    throw InvalidType(type);
}

static void throwNotFound(char code) {
    if (code == 'S') {
        throw StarterNotFound();
    }
    if (code == 'M') {
        throw MainNotFound();
    }
    throw DessertNotFound();
}

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

Item Menu::findFirst(string type) {
    char code = typeCode(type);
    for (int i = 0; i < maxSize; i++) {
        if (items[i] != NULL && items[i]->getType() == code) {
            return *items[i];
        }
    }
    throwNotFound(code);
    return Item(code, "", 0);  // never reached: throwNotFound always throws
}

Item Menu::findLast(string type) {
    char code = typeCode(type);
    for (int i = maxSize - 1; i >= 0; i--) {
        if (items[i] != NULL && items[i]->getType() == code) {
            return *items[i];
        }
    }
    throwNotFound(code);
    return Item(code, "", 0);  // never reached: throwNotFound always throws
}

float Menu::averagePrice(string type) {
    char code = typeCode(type);
    float total = 0;
    int count = 0;
    for (int i = 0; i < maxSize; i++) {
        if (items[i] != NULL && items[i]->getType() == code) {
            total += items[i]->getPrice();
            count++;
        }
    }
    if (count == 0) {
        throw NothingMatchingFilter(type);
    }
    return total / count;
}

int Menu::numberAbove(string type, float value) {
    char code = typeCode(type);
    int count = 0;
    for (int i = 0; i < maxSize; i++) {
        if (items[i] != NULL && items[i]->getType() == code && items[i]->getPrice() > value) {
            count++;
        }
    }
    if (count == 0) {
        throw NothingAboveMinimumValue();
    }
    return count;
}

int Menu::numberBelow(string type, float value) {
    char code = typeCode(type);
    int count = 0;
    for (int i = 0; i < maxSize; i++) {
        if (items[i] != NULL && items[i]->getType() == code && items[i]->getPrice() < value) {
            count++;
        }
    }
    if (count == 0) {
        throw NothingBelowMaximumValue();
    }
    return count;
}

int Menu::numberEqual(string type, float value) {
    char code = typeCode(type);
    int count = 0;
    for (int i = 0; i < maxSize; i++) {
        if (items[i] != NULL && items[i]->getType() == code && items[i]->getPrice() == value) {
            count++;
        }
    }
    if (count == 0) {
        throw NothingMatchingFilter(type);
    }
    return count;
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
