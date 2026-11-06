#include <iostream>
#include <string>

class SmartDevice {
 public:
  SmartDevice(std::string deviceID);
  void turnOn();
  void turnOff();
  void updatePower(double watts);
  bool getStatus() const;
  double getPower() const;

 private:
  std::string deviceID;
  bool isOn;
  double powerConsumption;
};

SmartDevice::SmartDevice(std::string deviceID)
    : deviceID(deviceID), isOn(false), powerConsumption(0) {}

void SmartDevice::turnOn() {
  isOn = true;
}

void SmartDevice::turnOff() {
  isOn = false;
}

void SmartDevice::updatePower(double watts) {
  powerConsumption = watts;
}

bool SmartDevice::getStatus() const {
  return isOn;
}

double SmartDevice::getPower() const {
  return powerConsumption;
}

int main() {
  SmartDevice lamp("lamp-01");
  lamp.turnOn();
  lamp.updatePower(9.5);
  std::cout << lamp.getStatus() << " " << lamp.getPower() << std::endl;
  lamp.turnOff();
  std::cout << lamp.getStatus() << std::endl;
  return 0;
}
