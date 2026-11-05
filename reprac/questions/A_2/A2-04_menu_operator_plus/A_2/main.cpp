
#include <iostream>

#include "Item.h"
#include "Menu.h"

using namespace std;

int main() {
    Menu menu(3);
    menu + new Item('S', "Garlic bread", 45.5);
    cout << menu;
    menu + new Item('M', "Beef burger", 120) + new Item('D', "Malva pudding", 60);
    cout << menu;
    menu + new Item('M', "Veg curry", 95.5);
    cout << menu;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Menu (max 3):
  [0] Garlic bread (S) R45.5
  [1] empty
  [2] empty
Menu (max 3):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] Malva pudding (D) R60
Menu (max 3):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] Malva pudding (D) R60
*/
