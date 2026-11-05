
#include <iostream>

#include "Item.h"
#include "Menu.h"

using namespace std;

int main() {
    Menu menu(2);
    menu += new Item('S', "Garlic bread", 45.5);
    menu += new Item('M', "Beef burger", 120);
    cout << menu;
    menu += new Item('D', "Malva pudding", 60);
    cout << menu;
    (menu += new Item('M', "Veg curry", 95.5)) += new Item('D', "Ice cream", 35);
    cout << menu;
    return 0;
}
/*
ExpectedOutput:
*/
/*
Menu (max 2):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
Menu (max 3):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] Malva pudding (D) R60
Menu (max 5):
  [0] Garlic bread (S) R45.5
  [1] Beef burger (M) R120
  [2] Malva pudding (D) R60
  [3] Veg curry (M) R95.5
  [4] Ice cream (D) R35
*/
