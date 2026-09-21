#ifndef CAMPUSGUARD_OPERATORCONSOLE_H
#define CAMPUSGUARD_OPERATORCONSOLE_H

#include <vector>
#include "Command.h"

// TODO(Ancheen): Invoker participant in the Command pattern.
// Keeps a history so CancelActionCommand (or a dedicated cancelLast())
// has something real to undo - this is what makes Cancel meaningful
// rather than decorative.
//
// Ownership: decide whether OperatorConsole owns the Command* objects
// it's given (likely yes - delete them in the destructor and when
// popped off history) and document that in the PDF.
class OperatorConsole {
public:
    OperatorConsole();
    ~OperatorConsole();

    void submit(Command* command); // executes and pushes to history
    void cancelLast();             // pops history and calls undo()

private:
    std::vector<Command*> history_; // owned
};

#endif // CAMPUSGUARD_OPERATORCONSOLE_H
