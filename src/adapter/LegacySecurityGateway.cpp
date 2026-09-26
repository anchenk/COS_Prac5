#include "../../include/adapter/LegacySecurityGateway.h"
#include <cstdio>
#include <iostream>

// TODO(Katlego): implement a believably "legacy" gateway.
LegacySecurityGateway::LegacySecurityGateway()
{
    std::cout << "LegacySecurityGateway initialized." << std::endl;
}
LegacySecurityGateway::~LegacySecurityGateway()
{
    std::cout << "LegacySecurityGateway destroyed." << std::endl;
}

int LegacySecurityGateway::sendRawSignal(int signalCode, const char *payload, int zoneId)
{
    // old system uses integer error codes

    if (signalCode <= 0)
    {
        std::cout << "[LegacySecurityGateway] ERROR: Invalid signal code." << std::endl;
        return -1;
    }

    if (payload == nullptr)
    {
        std::cout << "[LegacySecurityGateway] ERROR: Payload cannot be null." << std::endl;

        return -2;
    }

    if (zoneId <= 0)
    {
        std::cout << "[LegacySecurityGateway] ERROR: Invalid zone ID." << std::endl;
        return -3;
    }

    std::cout << "[LegacySecurityGateway] Sending raw signal: " << signalCode << ", payload: " << payload << ", zone ID: " << zoneId << std::endl;
    return 0;
}
