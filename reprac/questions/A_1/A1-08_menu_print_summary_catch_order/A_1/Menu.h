#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>

#include "Exception.h"
#include "Item.h"

using namespace std;

class Menu {
   private:
    int maxSize;
    Item** items;

   public:
    Menu(int maxSize);
    ~Menu();
    Menu& operator+(Item* item);
    Item findFirst(string type);
    int numberAbove(string type, float value);
    // Not in the published UML. Catches every exception; see QUESTION.md.
    bool printSummary(string type, float minPrice);

    friend ostream& operator<<(ostream& out, const Menu& menu);
};

#endif
