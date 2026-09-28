#ifndef CAMPUSGUARD_ISSUEALERTCOMMAND_H
#define CAMPUSGUARD_ISSUEALERTCOMMAND_H

#include "Command.h"
#include <string>

class AlertService;

// Concrete Command: broadcast an alert to a zone via AlertService.
// Receiver: AlertService

class IssueAlertCommand : public Command
{
public:
    IssueAlertCommand(AlertService *svc,
                      const std::string &message,
                      const std::string &zoneId);

    void execute() override;
    void undo() override;
    std::string describe() const override;

private:
    AlertService *svc; // not owned
    std::string message;
    std::string zoneId;
    bool executed = false;
    bool lastExecuteSucceeded = false;
};

#endif