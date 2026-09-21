#include "../../include/units/ResponseUnit.h"
#include "../../include/incident/IncidentCoordinator.h"

// TODO(Ancheen): base class plumbing; concrete subclasses
// (SecurityTeam.cpp etc.) go in this same directory.
ResponseUnit::ResponseUnit(const std::string& name, IIncidentMediator* mediator)
    : name_(name), mediator_(mediator) {}

ResponseUnit::~ResponseUnit() {}

std::string ResponseUnit::getName() const { return name_; }

void ResponseUnit::reportStatusChange(const std::string& event) {
    if (mediator_) {
        mediator_->notifyUnitStatusChanged(this, event);
    }
}
