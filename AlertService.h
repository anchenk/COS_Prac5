#ifndef ALERTSERVICE_H
#define ALERTSERVICE_H

#include <string>
#include <iostream>

class AlertService
{
private:
  bool active;

public:
  AlertService() : active(false) {};

  void issueEmergencyAlert(
      const std::string &area,
      const std::string &message)
  {
    active = true;

    std::cout << "[Alert Service] Emergency alert issued for " << area << ": " << message << std::endl;
  }

  void clearEmergencyAlert(
      const std::string &area)
  {
    active = false;

    std::cout << "[Alert Service] Emergency alert cleared for " << area << std::endl;
  }

  bool isAlertActive() const
  {
    return active;
  }
};

#endif