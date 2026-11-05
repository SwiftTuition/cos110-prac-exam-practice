
#include <iostream>

#include "Item.h"

using namespace std;

void compare(const Item& a, const Item& b) {
    cout << a << " vs " << b << ": ";
    cout << "== " << (a == b ? "true" : "false");
    cout << ", < " << (a < b ? "true" : "false") << endl;
}

int main() {
    Item burger('M', "Beef burger", 120);
    Item curry('M', "Veg curry", 95.5);
    Item burgerCopy(burger);
    Item cheapBurger('M', "Beef burger", 99.5);
    Item soup('S', "Soup", 95.5);
    compare(burger, burgerCopy);
    compare(burger, cheapBurger);
    compare(cheapBurger, burger);
    compare(curry, soup);
    compare(soup, curry);

    Item* list[4] = {&burger, &curry, &cheapBurger, &soup};
    int cheapest = 0;
    for (int i = 1; i < 4; i++) {
        if (*list[i] < *list[cheapest]) {
            cheapest = i;
        }
    }
    cout << "Cheapest: " << *list[cheapest] << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Beef burger (M) R120 vs Beef burger (M) R120: == true, < false
Beef burger (M) R120 vs Beef burger (M) R99.5: == false, < false
Beef burger (M) R99.5 vs Beef burger (M) R120: == false, < true
Veg curry (M) R95.5 vs Soup (S) R95.5: == false, < false
Soup (S) R95.5 vs Veg curry (M) R95.5: == false, < false
Cheapest: Veg curry (M) R95.5
*/
