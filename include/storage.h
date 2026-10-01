```cpp
#ifndef STORAGE_STORAGE_H
#define STORAGE_STORAGE_H

#include <string>
#include <vector>

namespace storage {

struct LogEntry {
    int term;
    int index;
    std::string command;
};

struct Snapshot {
    int last_index;
    std::vector<std::byte> data;
};

class Storage {
public:
    virtual ~Storage() = default;
    virtual void initialize(const std::string& id) = 0;
    virtual void appendLog(const std::vector<LogEntry>& entries) = 0;
    virtual std::vector<LogEntry> readLog(int index) = 0;
    virtual void readSnapshot(Snapshot& snapshot) = 0;
};

} // namespace storage

#endif // STORAGE_STORAGE_H
```