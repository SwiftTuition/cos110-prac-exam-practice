#include "Team.h"

int Team::assignIDs(string* ids, int n) {
    if (ids == NULL || n <= 0) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        cout << "Slot " << i << ": ";
        if (i >= size) {
            cout << "no such slot" << endl;
        } else if (members[i] == NULL) {
            cout << "empty" << endl;
        } else {
            cout << members[i]->getFirstName() << " " << members[i]->getSurName() << " -> ";
            // The try is inside the loop, so one bad ID does not stop the others.
            try {
                members[i]->setIDNum(ids[i]);
                cout << ids[i] << endl;
                count++;
            } catch (Exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
    }
    return count;
}
