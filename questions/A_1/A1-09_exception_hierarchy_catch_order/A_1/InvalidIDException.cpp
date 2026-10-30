#include "InvalidIDException.h"

InvalidIDException::InvalidIDException(string badID, string message) : Exception(message), badID(badID) {
}

string InvalidIDException::getBadID() {
    return badID;
}
