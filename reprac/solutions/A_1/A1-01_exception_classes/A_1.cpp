#include "Exception.h"

// msg is private, so every subclass sets it through the constructor of its direct base class.
Exception::Exception(string msg) : msg(msg) {
}

void Exception::printException() {
    cout << "Exception: " << msg << endl;
}

InvalidType::InvalidType(string type) : Exception("Invalid type: " + type) {
}

NothingMatchingFilter::NothingMatchingFilter(string filter) : Exception("Nothing matching filter: " + filter) {
}

NothingAboveMinimumValue::NothingAboveMinimumValue() : NothingMatchingFilter("above minimum value") {
}

NothingBelowMaximumValue::NothingBelowMaximumValue() : NothingMatchingFilter("below maximum value") {
}

NotFoundException::NotFoundException() : Exception("Item not found") {
}

StarterNotFound::StarterNotFound() : NotFoundException() {
}

MainNotFound::MainNotFound() : NotFoundException() {
}

DessertNotFound::DessertNotFound() : NotFoundException() {
}
