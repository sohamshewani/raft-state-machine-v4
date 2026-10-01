```cpp
#ifndef LEADER_ELECTION_LEADER_ELECTION_H
#define LEADER_ELECTION_LEADER_ELECTION_H

#include <string>
#include <unordered_map>
#include <functional>
#include <optional>

namespace leader_election {

struct VoteRequest {
    std::string candidate_id;
    int term;
};

struct VoteResponse {
    std::string voter_id;
    bool granted;
};

class LeaderElection {
public:
    LeaderElection(const std::string& id, int election_timeout_min, int election_timeout_max, int heartbeat_interval, std::shared_ptr<Storage> storage, std::shared_ptr<NetworkCommunication> network, std::function<void(const std::string&)> on_vote_request, std::function<void(const std::string&)> on_vote_response);
    ~LeaderElection();

    void start();
    void stop();

private:
    void run();
    void onElectionTimeout();
    void onHeartbeatTimeout();
    void onReceiveMessage(const NetworkMessage& message);

    std::string id;
    int term;
    std::optional<VoteRequest> vote_request;
    std::shared_ptr<Storage> storage;
    std::shared_ptr<NetworkCommunication> network;
    std::function<void(const std::string&)> on_vote_request;
    std::function<void(const std::string&)> on_vote_response;
};

} // namespace leader_election

#endif // LEADER_ELECTION_LEADER_ELECTION_H
```