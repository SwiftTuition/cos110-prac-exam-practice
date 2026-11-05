#include "Item.h"

ostream& operator<<(ostream& out, const Item& item) {
    // A friend may read the private members. Write to out, not to cout, and print no newline.
    out << item.name << " (" << item.type << ") R" << item.price;
    return out;
}
