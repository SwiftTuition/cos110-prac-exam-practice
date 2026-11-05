
#include <iostream>

#include "Exception.h"
#include "Item.h"
#include "Menu.h"

using namespace std;

void showFirst(Menu& menu, string type) {
    try {
        Item item = menu.findFirst(type);
        cout << "First " << type << ": " << item << endl;
    } catch (InvalidType& e) {
        cout << "InvalidType caught: ";
        e.printException();
    } catch (StarterNotFound& e) {
        cout << "StarterNotFound caught: ";
        e.printException();
    } catch (MainNotFound& e) {
        cout << "MainNotFound caught: ";
        e.printException();
    } catch (DessertNotFound& e) {
        cout << "DessertNotFound caught: ";
        e.printException();
    } catch (Exception& e) {
        cout << "Exception caught: ";
        e.printException();
    }
}

int main() {
    Menu menu(5);
    menu + new Item('S', "Garlic bread", 45.5) + new Item('M', "Beef burger", 120);
    menu + new Item('M', "Veg curry", 95.5) + new Item('D', "Malva pudding", 60);
    showFirst(menu, "Starter");
    showFirst(menu, "Main");
    showFirst(menu, "Dessert");
    showFirst(menu, "Drink");

    Menu dessertsOnly(3);
    dessertsOnly + new Item('D', "Ice cream", 35);
    showFirst(dessertsOnly, "Dessert");
    showFirst(dessertsOnly, "Starter");
    showFirst(dessertsOnly, "Main");

    Menu empty(2);
    showFirst(empty, "Dessert");
    return 0;
}
/*
ExpectedOutput:
*/
/*
First Starter: Garlic bread (S) R45.5
First Main: Beef burger (M) R120
First Dessert: Malva pudding (D) R60
InvalidType caught: Exception: Invalid type: Drink
First Dessert: Ice cream (D) R35
StarterNotFound caught: Exception: Item not found
MainNotFound caught: Exception: Item not found
DessertNotFound caught: Exception: Item not found
*/
