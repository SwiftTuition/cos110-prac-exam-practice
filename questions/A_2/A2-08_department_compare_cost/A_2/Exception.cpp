#include "Exception.h"

Exception::Exception(string message) : message(message) {
}

string Exception::what() {
    return message;
}

ostream& operator<<(ostream& out, const Exception& e) {
    out << "Exception: " << e.message;
    return out;
}
