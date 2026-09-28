#ifndef CAMPUSGUARD_CANCELACTIONCOMMAND_H
#define CAMPUSGUARD_CANCELACTIONCOMMAND_H

#include "Command.h"
#include <string>

class OperatorConsole;

// Concrete Command that undoes the previous command on the invoker.
// Note: this command is NOT pushed onto history (see OperatorConsole::submit);
// it acts purely as a "meta" command. It holds the invoker so it can call
// cancelLast(), which in turn calls undo() on the real previous command.
class CancelActionCommand : public Command
{
public:
    explicit CancelActionCommand(OperatorConsole *console);

    void execute() override;
    void undo() override;
    std::string describe() const override;

private:
    OperatorConsole *console_;
};

#endif