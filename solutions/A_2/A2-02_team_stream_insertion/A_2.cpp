#include "Team.h"

ostream& operator<<(ostream& out, const Team& t) {
    // t is const, so getMemberCount() and operator[] (not const) cannot be called. Use the members.
    int count = 0;
    for (int i = 0; i < t.size; i++) {
        if (t.members[i] != NULL) {
            count++;
        }
    }
    out << "Team (" << count << "/" << t.size << "):" << endl;
    if (count == 0) {
        out << "  (no members)" << endl;
    }
    for (int i = 0; i < t.size; i++) {
        if (t.members[i] != NULL) {
            out << "  " << *t.members[i] << endl;
        }
    }
    return out;
}
