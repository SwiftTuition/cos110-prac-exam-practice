#include "Item.h"

bool Item::operator==(const Item& other) const {
    // All three members must match.
    return type == other.type && name == other.name && price == other.price;
}

bool Item::operator<(const Item& other) const {
    // Only the price decides. Equal prices give false.
    return price < other.price;
}
