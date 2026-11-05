#include "Exception.h"

ostream& operator<<(ostream& out, const Exception& e) {
    // msg is private; a friend may read it. No newline, and no call to printException():
    // e is const and printException() is not a const member function.
    out << "Exception: " << e.msg;
    return out;
}
