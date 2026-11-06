#include <iostream>
#include <string>

class Bank {
 public:
  Bank(std::string bankName = "myBank", double balance = 0.0);
  void print() const;

 private:
  std::string bankName;
  double vaultBalance;
};

Bank::Bank(std::string bankName, double balance) {
  this->bankName = bankName;
  vaultBalance = balance;
}

void Bank::print() const {
  std::cout << bankName << " " << vaultBalance << std::endl;
}

int main() {
  Bank b1;
  Bank b2("Absa");
  Bank* bptr = new Bank("Capitec", 1000);
  b1.print();
  b2.print();
  bptr->print();
  delete bptr;
  return 0;
}
