#include "Counter.h"

int Counter::maxLimit = 100;

Counter::Counter() : count(0) {}

void Counter::increment(int value) {
  if (this->count + value <= Counter::maxLimit) {
    this->count += value;
  }
}

int Counter::getCount() const {
  return this->count;
}

void Counter::setMaxLimit(int limit) {
  Counter::maxLimit = limit;
}
