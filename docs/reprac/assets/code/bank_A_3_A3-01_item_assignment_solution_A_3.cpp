#include "Item.h"

Item& Item::operator=(const Item& other) {
    if (this == &other) {
        return *this;
    }
    type = other.type;
    name = other.name;
    price = other.price;
    return *this;
}
