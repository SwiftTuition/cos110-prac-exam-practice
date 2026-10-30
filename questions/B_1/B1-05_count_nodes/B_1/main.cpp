#include <iostream>

#include "List.h"

using namespace std;

int main() {
    List<int> list;
    list.prepend(40);
    list.prepend(30);
    list.prepend(20);
    list.prepend(10);
    cout << list << endl;

    cout << "Nodes from the head: " << list.countNodes(list.head()) << endl;
    cout << "Nodes from the second node: " << list.countNodes(list.head()->next()) << endl;

    List<int> empty;
    cout << "Nodes in an empty list: " << empty.countNodes(empty.head()) << endl;
    return 0;
}
/*
ExpectedOutput:
*/
/*
10->20->30->40
Nodes from the head: 4
Nodes from the second node: 3
Nodes in an empty list: 0
*/
