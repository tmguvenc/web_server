#ifndef MESSAGE_MANAGER_H_
#define MESSAGE_MANAGER_H_

#include "queue_with_id.h"
#include "payload.h"
#include "common.h"

struct lws;

namespace ws {

using Queue = QueueWithId<Payload, Mutex>;

class MessageManager {
public:
  void CreateMessage(
    const uint64_t client_id, const void* data, const uint64_t len);

  void SendMessage(lws* wsi, const uint64_t client_id);

  static MessageManager* Create(lws* wsi);
  static void Destroy(lws* wsi);

private:
  Queue* send_queue_;
};

MessageManager* GetMessageManager(lws* wsi);

}  // namespace ws

#endif  // !MESSAGE_MANAGER_H_
