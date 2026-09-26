#ifndef CAMPUSGUARD_LEGACYSECURITYGATEWAY_H
#define CAMPUSGUARD_LEGACYSECURITYGATEWAY_H

#include <string>
#include <iostream>
// Adapter pattern ADAPTEE - the pre-existing/legacy/external service
// with an interface that does NOT match INotificationChannel.
//
// TODO(Katlego): flesh this out with genuinely awkward signatures
// (integer status codes, raw char* payloads, a different call order,
// etc.) so the adapter has real translation work to do. Then write
// LegacyGatewayAdapter : public INotificationChannel that owns/wraps
// an instance of this class and translates sendAlert(...) calls into
// this class's native calls.
class LegacySecurityGateway
{
public:
    LegacySecurityGateway()
    {
        std::cout << "LegacySecurityGateway initialized." << std::endl;
    }
    ~LegacySecurityGateway()
    {
        std::cout << "LegacySecurityGateway destroyed." << std::endl;
    }

    // Deliberately mismatched interface vs. INotificationChannel::sendAlert.
    int sendRawSignal(int signalCode, const char *payload, int zoneId)
    {
        if (signalCode <= 0)
        {
            std::cerr << "Error: Invalid signal code." << std::endl;
            return -1; // Error code for invalid signal
        }

        if (payload == nullptr)
        {
            std::cerr << "Error: Payload cannot be null." << std::endl;
            return -2; // Error code for null payload
        }

        if (zoneId < 0)
        {
            std::cerr << "Error: Zone ID cannot be negative." << std::endl;
            return -3; // Error code for invalid zone ID
        }

        std::cout << "[LegacySecurityGateway] Sending raw signal: " << signalCode
                  << ", Payload: " << payload
                  << ", Zone ID: " << zoneId << std::endl;
        return 0; // Success code
    }
};

#endif // CAMPUSGUARD_LEGACYSECURITYGATEWAY_H
