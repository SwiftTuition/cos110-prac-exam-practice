#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

using namespace std;

class Item {
   private:
    char type;
    string name;
    float price;

   public:
    Item(char type, string name, float price);
    Item(const Item& other);
    ~Item();
    char getType() const;
    string getName() const;
    float getPrice() const;

    // Not in the published UML.
    bool operator==(const Item& other) const;
    bool operator<(const Item& other) const;

    friend ostream& operator<<(ostream& out, const Item& item);
};

#endif
