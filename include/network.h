```cpp
#ifndef NETWORK_NETWORK_H
#define NETWORK_NETWORK_H

#include <string>
#include <memory>

namespace network {

using NetworkMessage = std::string;

enum class MessageType { VOTE_REQUEST, VOTE_RESPONSE, APPEND_ENTRIES };

struct NetworkMessage {
    MessageType type;
    std::string sender;
    std::string receiver;
    std::optional<LogEntry> log_entry;
};

class NetworkCommunication {
public:
    virtual ~NetworkCommunication() = default;
    virtual void send(const NetworkMessage& message) = 0;
    virtual void receive(const std::function<void(const NetworkMessage&)>& callback) = 0;
};

} // namespace network

#endif // NETWORK_NETWORK_H
```