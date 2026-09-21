#ifndef ACCESSCONTROLSYSTEM_H
#define ACCESSCONTROLSYSTEM_H

#include <map>
#include <string>
#include <iostream>

class AccessControlSystem
{
private:
  std::map<std::string, std::string> areaStates;

public:
  void restrictArea(
      const std::string &area)
  {
    areaStates[area] = "RESTRICTED";

    std::cout << "[Access Control] restricted normal entry to " << area << std::endl;
  }

  void openEmergencyExits(
      const std::string &area)
  {
    std::cout << "[Access Control] Emergency exists opened to " << area << std::endl;
  }

  void restoreNormalAccess(
      const std::string &area)
  {
    areaStates[area] = "NORMAL";

    std::cout << "[Access Control] Normal access restored to " << area << std::endl;
  }

  std::string getAreaState(
      const std::string &area) const
  {
    std::map<std::string, std::string>::const_iterator it = areaStates.find(area);

    if (it == areaStates.end())
    {
      return "NORMAL";
    }
    return it->second;
  }
};

#endif