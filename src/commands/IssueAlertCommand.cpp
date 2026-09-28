#include "IssueAlertCommand.h"
#include "AlertService.h"
#include <iostream>

IssueAlertCommand::IssueAlertCommand(AlertService *svc,
                                     const std::string &message,
                                     const std::string &zoneId)
    : svc(svc), message(message), zoneId(zoneId) {}

void IssueAlertCommand::execute()
{
    if (!svc)
    {
        std::cout << "[IssueAlertCommand] no receiver; aborting.\n";
        return;
    }
    std::cout << "[Command] execute: " << describe() << "\n";
    lastExecuteSucceeded = svc->broadcastAlert(message, zoneId);
    executed = true;

    if (!lastExecuteSucceeded)
    {
        std::cout << "[IssueAlertCommand] broadcast failed for zone '"
                  << zoneId << "'.\n";
    }
}

void IssueAlertCommand::undo()
{
    if (!executed)
        return;

    if (!lastExecuteSucceeded)
    {
        std::cout << "[Command] undo skipped: broadcast never succeeded.\n";
        executed = false;
        return;
    }

    std::cout << "[Command] undo: " << describe()
              << " -> no retraction API on AlertService; "
                 "logging acknowledgement instead.\n";
    std::cout << "[IssueAlertCommand] Alert for zone '" << zoneId
              << "' acknowledged as delivered (not retracted).\n";

    executed = false;
}

std::string IssueAlertCommand::describe() const
{
    return "IssueAlert(zone=" + zoneId + ", \"" + message + "\")";
}