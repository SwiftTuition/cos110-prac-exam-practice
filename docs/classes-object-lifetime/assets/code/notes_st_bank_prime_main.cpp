#include <iostream>
#include <string>

class Bank {
 public:
  Bank(std::string name) : bankName(name) {}
  static double getPrimeRate();
  static void setPrimeRate(double rate);

 private:
  std::string bankName;
  static double primeRate;
};

double Bank::primeRate = 0.105;

double Bank::getPrimeRate() {
  return primeRate;
}

void Bank::setPrimeRate(double rate) {
  primeRate = rate;
}

int main() {
  std::cout << Bank::getPrimeRate() << std::endl;
  Bank absa("Absa");
  Bank fnb("FNB");
  Bank::setPrimeRate(0.11);
  std::cout << Bank::getPrimeRate() << std::endl;
  return 0;
}
