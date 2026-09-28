#ifndef CAMPUSGUARD_ISSUEALERTCOMMAND_H
#define CAMPUSGUARD_ISSUEALERTCOMMAND_H

#include "Command.h"
#include <string>

class AlertService;

class IssueAlertCommand : public Command {
public:
    IssueAlertCommand(AlertService* svc, const std::string& message);

    void execute() override;
    void undo()    override;
    std::string describe() const override;

private:
    AlertService* svc;
    std::string message;
    bool wasActive = false;
    bool executed  = false;
};

#endif