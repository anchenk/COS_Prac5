#include "CancelActionCommand.h"
#include "OperatorConsole.h"
#include <iostream>

CancelActionCommand::CancelActionCommand(OperatorConsole *console)
    : console_(console) {}

void CancelActionCommand::execute()
{
    if (!console_)
    {
        std::cout << "[CancelAction] no invoker.\n";
        return;
    }
    std::cout << "[Command] execute: " << describe() << "\n";
    console_->cancelLast();
}

void CancelActionCommand::undo()
{
    std::cout << "[CancelAction] CancelAction itself cannot be undone "
                 "(no meaningful inverse).\n";
}

std::string CancelActionCommand::describe() const
{
    return "CancelAction";
}