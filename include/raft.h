```cpp
#ifndef RAFT_RAFT_H
#define RAFT_RAFT_H

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <optional>

#include "network.h"
#include "storage.h"
#include "state_machine.h"
#include "leader_election.h"
#include "log_compaction.h"

namespace raft {

enum class Role { FOLLOWER, CANDIDATE, LEADER };

struct Config {
    std::string id;
    int election_timeout_min;
    int election_timeout_max;
    int heartbeat_interval;
    std::shared_ptr<Storage> storage;
    std::shared_ptr<NetworkCommunication> network;
    std::function<void(const std::string&)> on_vote_request;
    std::function<void(const std::string&)> on_vote_response;
};

struct State {
    Role role;
    int term;
    std::string vote_for;
    std::optional<LogEntry> last_applied;
    int commit_index;
    int next_index;
    int match_index;
};

class Raft : public std::enable_shared_from_this<Raft> {
public:
    Raft(const Config& config);
    ~Raft();

    void start();
    void stop();

private:
    void handleElection();
    void handleHeartbeat();
    void handleAppendEntries();
    void handleVoteRequest();
    void handleVoteResponse();

    void updateLog(const std::vector<LogEntry>& entries);

    Config config;
    State state;
    std::shared_ptr<StateMachine> state_machine;
    std::shared_ptr<LeaderElection> leader_election;
    std::shared_ptr<LogCompaction> log_compaction;

    std::shared_ptr<Storage> storage;
    std::shared_ptr<NetworkCommunication> network;

    void run();
    void onElectionTimeout();
    void onHeartbeatTimeout();
    void onReceiveMessage(const NetworkMessage& message);
};

} // namespace raft

#endif // RAFT_RAFT_H
```