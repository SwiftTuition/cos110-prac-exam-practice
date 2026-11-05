#include "Menu.h"

bool Menu::printSummary(string type, float minPrice) {
    try {
        Item first = findFirst(type);
        int count = numberAbove(type, minPrice);
        // Both calls worked, so print the whole line now.
        cout << type << ": first is " << first << ", " << count << " above R" << minPrice << endl;
        return true;
    } catch (DessertNotFound& e) {
        // A derived class must come before its base class (NotFoundException).
        cout << "No desserts yet. ";
        e.printException();
    } catch (NotFoundException& e) {
        cout << "Not on the menu. ";
        e.printException();
    } catch (NothingAboveMinimumValue& e) {
        cout << "Nothing above R" << minPrice << ". ";
        e.printException();
    } catch (Exception& e) {
        // The base class of all the others comes last.
        cout << "Request failed. ";
        e.printException();
    }
    return false;
}
