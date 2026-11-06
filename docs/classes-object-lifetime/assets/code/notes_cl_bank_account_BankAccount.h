#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>

class BankAccount {
 public:
  BankAccount(std::string owner, std::string pin);
  bool isPinCorrect(std::string pin) const;
  void deposit(double amount);
  double withdraw(double amount);
  double getBalance() const;

 private:
  std::string owner;
  std::string pin;
  double balance;
};

#endif
