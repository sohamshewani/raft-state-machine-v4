```cpp
#ifndef LOG_COMPACTION_LOG_COMPACTION_H
#define LOG_COMPACTION_LOG_COMPACTION_H

#include <string>
#include <unordered_map>

namespace log_compaction {

using LogEntry = raft::LogEntry;

class LogCompaction {
public:
    LogCompaction(const std::string& id, std::shared_ptr<Storage> storage);
    ~LogCompaction();

    void start();
    void stop();

private:
    void run();
    void onLogEntry(const LogEntry& entry);

    std::string id;
    std::shared_ptr<Storage> storage;
};

} // namespace log_compaction

#endif // LOG_COMPACTION_LOG_COMPACTION_H
```