#ifndef QUEUE_WITH_ID_HPP
#define QUEUE_WITH_ID_HPP

#include <unordered_map>
#include <optional>
#include "lock_guard.h"

template<typename T, typename Mutex>
class QueueWithId {
public:
  void enqueue(uint64_t id, T item) {
    LockGuard<Mutex> lg(mutex);
    message_queue.insert({ id, item });
  }

  std::optional<T> dequeue(uint64_t id) {
    LockGuard<Mutex> lg(mutex);
    if (const auto it = message_queue.find(id); it != message_queue.end()) {
      const auto ret = it->second;
      message_queue.erase(it);
      return ret;
    }
    return {};
  }

private:
  std::unordered_multimap<uint64_t, T> message_queue;
  Mutex mutex;
};

#endif  // !QUEUE_WITH_ID_HPP