#include "../../include/adapter/LegacySecurityGateway.h"
#include <cstdio>

// TODO(Katlego): implement a believably "legacy" gateway.
LegacySecurityGateway::LegacySecurityGateway() {}
LegacySecurityGateway::~LegacySecurityGateway() {}

int LegacySecurityGateway::sendRawSignal(int signalCode, const char* payload, int zoneId) {
    // TODO: simulate legacy behaviour, return a raw status code
    return 0;
}
