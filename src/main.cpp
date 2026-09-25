#include <iostream>
#include "../include/incident/Incident.h"
#include "../include/incident/ReportedState.h"
#include "../include/incident/IncidentCoordinator.h"
#include "../include/units/ResponseUnit.h"

// ---------------------------------------------------------------------
// TEMPORARY test-only subclass, for Musa's local testing before Anchen's
// real ResponseUnit subclasses exist. DELETE this before final submission.
// ---------------------------------------------------------------------
class TestUnit : public ResponseUnit {
public:
    TestUnit(const std::string& name, IIncidentMediator* mediator)
        : ResponseUnit(name, mediator), status_("idle") {}

    void dispatch(const std::string& location) override {
        status_ = "arrived";
        std::cout << getName() << " dispatched to " << location << "\n";
        reportStatusChange("arrived"); // triggers the Mediator
    }

    void recall() override {
        status_ = "idle";
        std::cout << getName() << " recalled.\n";
    }

    std::string getStatus() const override {
        return status_;
    }

private:
    std::string status_;
};

int main() {
    std::cout << "=== CampusGuard - Musa's local test ===\n\n";

    // --- Test 1: State pattern chain ---
    std::cout << "--- Testing Incident State transitions ---\n";
    Incident incident("INC-001", "Fire", "Engineering Building", 4);
    incident.setState(new ReportedState());

    std::cout << "Current state: " << incident.currentStateName() << "\n";
    incident.advanceState(); // Reported -> Dispatched
    std::cout << "Current state: " << incident.currentStateName() << "\n";
    incident.advanceState(); // Dispatched -> Contained
    std::cout << "Current state: " << incident.currentStateName() << "\n";
    incident.advanceState(); // Contained -> Resolved
    std::cout << "Current state: " << incident.currentStateName() << "\n";

    bool advanced = incident.advanceState(); // should FAIL - Resolved is terminal
    std::cout << "Attempted advance from Resolved, succeeded? "
              << (advanced ? "true" : "false") << "\n\n";

    // --- Test 2: Mediator pattern ---
    std::cout << "--- Testing Mediator coordination ---\n";
    IncidentCoordinator coordinator;
    TestUnit security("SecurityTeam-1", &coordinator);
    TestUnit medical("MedicalTeam-1", &coordinator);

    coordinator.registerUnit(&security);
    coordinator.registerUnit(&medical);

    security.dispatch("Engineering Building"); // should trigger mediator to notify medical

    return 0;
}