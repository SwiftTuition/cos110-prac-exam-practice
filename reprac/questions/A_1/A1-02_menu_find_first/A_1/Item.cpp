#include "Item.h"

Item::Item(char type, string name, float price) : type(type), name(name), price(price) {
}

Item::Item(const Item& other) : type(other.type), name(other.name), price(other.price) {
}

Item::~Item() {
}

char Item::getType() const {
    return type;
}

string Item::getName() const {
    return name;
}

float Item::getPrice() const {
    return price;
}

ostream& operator<<(ostream& out, const Item& item) {
    out << item.name << " (" << item.type << ") R" << item.price;
    return out;
}
