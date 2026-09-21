#ifndef LEGACYCAMPUSSECURITYGATEWAY_H
#define LEGACYCAMPUSSECURITYGATEWAY_H

#include <iostream>
class LegacyCampusSecurityGateway
{
public:
  int sendLegacyPacket(const char *packedMessage, int priorityCode)
  {

    if (packedMessage == 0 || priorityCode < 1 || priorityCode > 3)
    {
      std::cout << "[Legacy Gateway] ERROR: invalid legacy packet" << std::endl;

      return -1;
    }

    std::cout << "[Legacy Gateway] packet: " << packedMessage << " with priority code: " << priorityCode << std::endl;
    return 0;
  }
};

#endif