```cpp
#ifndef STATE_MACHINE_STATE_MACHINE_H
#define STATE_MACHINE_STATE_MACHINE_H

#include <string>
#include <unordered_map>

namespace state_machine {

using Command = std::string;

class StateMachine {
public:
    virtual ~StateMachine() = default;
    virtual void applyCommand(const Command& command) = 0;
};

} // namespace state_machine

#endif // STATE_MACHINE_STATE_MACHINE_H
```