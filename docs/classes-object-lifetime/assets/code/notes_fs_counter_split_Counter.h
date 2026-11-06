#ifndef COUNTER_H
#define COUNTER_H

class Counter {
 private:
  int count;
  static int maxLimit;

 public:
  Counter();
  void increment(int value);
  int getCount() const;
  static void setMaxLimit(int limit);
};

#endif
