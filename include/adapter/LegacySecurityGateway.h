#ifndef CAMPUSGUARD_LEGACYSECURITYGATEWAY_H
#define CAMPUSGUARD_LEGACYSECURITYGATEWAY_H

// Adapter pattern ADAPTEE - the pre-existing/legacy/external service
// with an interface that does NOT match INotificationChannel.
//
// TODO(Katlego): flesh this out with genuinely awkward signatures
// (integer status codes, raw char* payloads, a different call order,
// etc.) so the adapter has real translation work to do. Then write
// LegacyGatewayAdapter : public INotificationChannel that owns/wraps
// an instance of this class and translates sendAlert(...) calls into
// this class's native calls.
class LegacySecurityGateway {
public:
    LegacySecurityGateway();
    ~LegacySecurityGateway();

    // Deliberately mismatched interface vs. INotificationChannel::sendAlert.
    int sendRawSignal(int signalCode, const char* payload, int zoneId);
};

#endif // CAMPUSGUARD_LEGACYSECURITYGATEWAY_H
