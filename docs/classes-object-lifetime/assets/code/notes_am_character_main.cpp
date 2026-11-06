#include <iostream>

class Character {
 private:
  int health;
  int mana;

 public:
  Character() : health(100), mana(50) {}
  int getHealth() const;
  void takeDamage(int amount);
  void printStatus() const;
  void setMana(int m);
};

int Character::getHealth() const {
  return health;
}

void Character::takeDamage(int amount) {
  health -= amount;
}

void Character::printStatus() const {
  std::cout << "health " << health << ", mana " << mana << std::endl;
}

void Character::setMana(int m) {
  mana = m;
}

int main() {
  Character hero;
  hero.takeDamage(30);
  hero.setMana(20);
  hero.printStatus();
  std::cout << hero.getHealth() << std::endl;
  return 0;
}
