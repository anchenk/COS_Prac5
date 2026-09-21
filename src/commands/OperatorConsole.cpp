#include "../../include/commands/OperatorConsole.h"

// TODO(Ancheen): implement submit/cancelLast and destructor cleanup
// of any remaining Command* in history_ (ownership decision).
OperatorConsole::OperatorConsole() {}

OperatorConsole::~OperatorConsole() {
    // TODO: delete remaining Command* in history_
}

void OperatorConsole::submit(Command* command) {
    command->execute();
    history_.push_back(command);
}

void OperatorConsole::cancelLast() {
    if (!history_.empty()) {
        Command* last = history_.back();
        last->undo();
        history_.pop_back();
        // TODO: decide whether to delete last here
    }
}
