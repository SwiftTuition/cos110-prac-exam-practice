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
    Item findLast(string type);

    friend ostream& operator<<(ostream& out, const Menu& menu);
};

#endif
