
#include <iostream>

#include "Exception.h"
#include "Item.h"
#include "Menu.h"

using namespace std;

void show(Menu& menu, string type, float value) {
    try {
        int count = menu.numberAbove(type, value);
        cout << type << " above R" << value << ": " << count << endl;
    } catch (InvalidType& e) {
        cout << "InvalidType caught: ";
        e.printException();
    } catch (NothingAboveMinimumValue& e) {
        cout << "NothingAboveMinimumValue caught: ";
        e.printException();
    } catch (NothingBelowMaximumValue& e) {
        cout << "NothingBelowMaximumValue caught: ";
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
    show(menu, "Main", 100);
    show(menu, "Main", 90);
    show(menu, "Main", 120);
    show(menu, "Starter", 45.5);
    show(menu, "Dessert", 100);
    show(menu, "Drink", 10);
    return 0;
}
/*
ExpectedOutput:
*/
/*
Main above R100: 1
Main above R90: 2
NothingAboveMinimumValue caught: Exception: Nothing matching filter: above minimum value
Starter above R45.5: 1
NothingAboveMinimumValue caught: Exception: Nothing matching filter: above minimum value
InvalidType caught: Exception: Invalid type: Drink
*/
