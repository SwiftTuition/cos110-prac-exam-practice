#include "Exception.h"

Exception::~Exception() {
}

ostream& operator<<(ostream& out, const Exception& e) {
    out << "Exception: " << e.msg;
    return out;
}
