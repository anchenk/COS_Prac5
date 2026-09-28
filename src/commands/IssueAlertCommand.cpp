#include "IssueAlertCommand.h"
#include "AlertService.h"
#include <iostream>

IssueAlertCommand::IssueAlertCommand(AlertService *svc,
                                     const std::string &message)
    : svc(svc), message(message) {}

void IssueAlertCommand::execute()
{
    if (!svc)
    {
        std::cout << "[IssueAlert] no receiver.\n";
        return;
    }
    std::cout << "[Command] execute: " << describe() << "\n";
    wasActive = svc->isAlertActive();
    svc->broadcastAlert(message);
    executed = true;
}

void IssueAlertCommand::undo()
{
    if (!executed || !svc)
        return;
    std::cout << "[Command] undo: " << describe() << "\n";
    if (wasActive)
    {
        std::cout << "[IssueAlert] previous alert was already active; "
                     "leaving service as-is (no rollback).\n";
    }
    else
    {
        svc->clearAlert();
    }
    executed = false;
}

std::string IssueAlertCommand::describe() const
{
    return "IssueAlert(\"" + message + "\")";
}