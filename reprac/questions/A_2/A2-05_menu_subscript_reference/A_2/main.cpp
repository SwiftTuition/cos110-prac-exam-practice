
#include <iostream>

#include "Item.h"
#include "Menu.h"

using namespace std;

int main() {
    Menu menu(3);
    menu + new Item('S', "Garlic bread", 45.5) + new Item('M', "Beef burger", 120);
    cout << "Slot 1: " << *menu[1] << endl;
    if (menu[2] == NULL) {
        cout << "Slot 2 is empty" << endl;
    }

    menu[2] = new Item('D', "Malva pudding", 60);
    delete menu[0];
    menu[0] = new Item('S', "Soup", 50);
    cout << menu;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Slot 1: Beef burger (M) R120
Slot 2 is empty
Menu (max 3):
  [0] Soup (S) R50
  [1] Beef burger (M) R120
  [2] Malva pudding (D) R60
*/
