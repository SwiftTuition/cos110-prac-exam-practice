
#include <iostream>

#include "Item.h"
#include "Menu.h"

using namespace std;

int main() {
    Menu menu(4);
    menu + new Item('S', "Garlic bread", 45.5) + new Item('M', "Beef burger", 120);
    menu + new Item('D', "Malva pudding", 60);
    menu - "Beef burger";
    cout << menu;
    menu - "Pizza";
    menu - "Garlic bread";
    cout << menu;
    menu + new Item('M', "Veg curry", 95.5);
    cout << menu;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Menu (max 4):
  [0] Garlic bread (S) R45.5
  [1] Malva pudding (D) R60
  [2] empty
  [3] empty
Menu (max 4):
  [0] Malva pudding (D) R60
  [1] empty
  [2] empty
  [3] empty
Menu (max 4):
  [0] Malva pudding (D) R60
  [1] Veg curry (M) R95.5
  [2] empty
  [3] empty
*/
