
#include <iostream>

#include "Exception.h"
#include "Item.h"
#include "Menu.h"

using namespace std;

void check(Menu& menu, string type, float minPrice) {
    bool ok = menu.printSummary(type, minPrice);
    cout << "  returned " << (ok ? "true" : "false") << endl;
}

int main() {
    Menu menu(5);
    menu + new Item('S', "Garlic bread", 45.5) + new Item('M', "Beef burger", 120);
    menu + new Item('M', "Veg curry", 95.5);
    check(menu, "Main", 100);
    check(menu, "Starter", 45.5);
    check(menu, "Dessert", 10);
    check(menu, "Drink", 10);

    Menu empty(2);
    check(empty, "Starter", 0);
    check(empty, "Main", 0);
    return 0;
}
/*
ExpectedOutput:
*/
/*
Main: first is Beef burger (M) R120, 1 above R100
  returned true
Nothing above R45.5. Exception: Nothing matching filter: above minimum value
  returned false
No desserts yet. Exception: Item not found
  returned false
Request failed. Exception: Invalid type: Drink
  returned false
Not on the menu. Exception: Item not found
  returned false
Not on the menu. Exception: Item not found
  returned false
*/
