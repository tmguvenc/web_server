#ifndef COMMON_H
#define COMMON_H

#include "empty_mutex.h"
#include <vector>
#include <unordered_map>

namespace ws {
using Mutex = EmptyMutex;

struct Message {
  std::string msg_name{};
  std::vector<std::string> field_names{};
};

struct ClientRequestMessage {
  std::string device_name;
  std::vector<Message> messages;
};

}  // namespace ws

#endif  // !COMMON_H
