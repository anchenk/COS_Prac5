#include "../../include/incident/Incident.h"
#include <algorithm>
#include <stdexcept>

Incident::Incident(const std::string& id, const std::string& type,
                     const std::string& location, int severity)
    : id_(id), type_(type), location_(location), severity_(severity), state_(nullptr) {
    if (severity < 1 || severity > 5) {
        throw std::invalid_argument("Incident severity must be between 1 and 5");
    }
}

Incident::~Incident() {
    delete state_;
    // observers_ are NOT owned by Incident - they're external listeners
    // (loggers, dashboards) that outlive individual incidents.
}

std::string Incident::getId() const { return id_; }
std::string Incident::getType() const { return type_; }
std::string Incident::getLocation() const { return location_; }
int Incident::getSeverity() const { return severity_; }

void Incident::attach(IIncidentObserver* observer) {
    observers_.push_back(observer);
}

void Incident::detach(IIncidentObserver* observer) {
    observers_.erase(
        std::remove(observers_.begin(), observers_.end(), observer),
        observers_.end()
    );
}

void Incident::notify(const std::string& reason) {
    for (std::vector<IIncidentObserver*>::iterator it = observers_.begin();
         it != observers_.end(); ++it) {
        (*it)->onIncidentChanged(*this, reason);
    }
}