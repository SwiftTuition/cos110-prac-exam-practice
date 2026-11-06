#include <iostream>
#include "BankAccount.h"

int main() {
  BankAccount account("Thandi", "4321");
  account.deposit(500);
  std::cout << account.withdraw(200) << std::endl;
  std::cout << account.withdraw(900) << std::endl;
  std::cout << account.getBalance() << std::endl;
  std::cout << account.isPinCorrect("1234") << std::endl;
  return 0;
}
