#include "../../include/incident/Incident.h"

// TODO(Musa): implement constructor, destructor (delete state_),
// state delegation, and observer notify loop.
Incident::Incident(const std::string& id, const std::string& type,
                     const std::string& location, int severity)
    : id_(id), type_(type), location_(location), severity_(severity), state_(nullptr) {}

Incident::~Incident() {
    // TODO: delete state_;
}

bool Incident::advanceState() {
    // TODO: delegate to state_->advance(*this)
    return false;
}

void Incident::setState(IncidentState* newState) {
    // TODO: delete old state_, assign newState
    state_ = newState;
}

std::string Incident::currentStateName() const {
    // TODO: return state_->name();
    return "";
}

void Incident::attach(IIncidentObserver* observer) {
    observers_.push_back(observer);
}

void Incident::detach(IIncidentObserver* observer) {
    // TODO: remove from observers_
}

void Incident::notify(const std::string& reason) {
    // TODO: loop observers_, call onIncidentChanged(*this, reason)
}

std::string Incident::getId() const { return id_; }
std::string Incident::getType() const { return type_; }
std::string Incident::getLocation() const { return location_; }
int Incident::getSeverity() const { return severity_; }
