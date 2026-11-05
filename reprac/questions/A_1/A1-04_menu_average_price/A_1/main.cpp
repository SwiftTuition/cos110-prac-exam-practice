
#include <iostream>

#include "Exception.h"
#include "Item.h"
#include "Menu.h"

using namespace std;

void showAverage(Menu& menu, string type) {
    try {
        float average = menu.averagePrice(type);
        cout << "Average " << type << " price: R" << average << endl;
    } catch (InvalidType& e) {
        cout << "InvalidType caught: ";
        e.printException();
    } catch (NothingMatchingFilter& e) {
        cout << "NothingMatchingFilter caught: ";
        e.printException();
    } catch (Exception& e) {
        cout << "Exception caught: ";
        e.printException();
    }
}

int main() {
    Menu menu(6);
    menu + new Item('S', "Garlic bread", 45.5) + new Item('M', "Beef burger", 120);
    menu + new Item('M', "Veg curry", 95.5) + new Item('D', "Malva pudding", 60);
    menu + new Item('S', "Soup", 50);
    showAverage(menu, "Starter");
    showAverage(menu, "Main");
    showAverage(menu, "Dessert");
    showAverage(menu, "Drink");

    Menu small(2);
    small + new Item('M', "Beef burger", 120);
    showAverage(small, "Main");
    showAverage(small, "Dessert");
    showAverage(small, "Starter");
    return 0;
}
/*
ExpectedOutput:
*/
/*
Average Starter price: R47.75
Average Main price: R107.75
Average Dessert price: R60
InvalidType caught: Exception: Invalid type: Drink
Average Main price: R120
NothingMatchingFilter caught: Exception: Nothing matching filter: Dessert
NothingMatchingFilter caught: Exception: Nothing matching filter: Starter
*/
