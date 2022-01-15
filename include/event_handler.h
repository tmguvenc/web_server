#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#include <libwebsockets.h>
#include <functional>
#include <unordered_map>

struct lws;

namespace ws {

class MessageManager;

using CallbackHandler = std::function<void(lws* wsi,
  const lws_callback_reasons reason,
  void* user_data,
  void* in,
  const size_t len)>;

using CallbackMap = std::unordered_map<lws_callback_reasons, CallbackHandler>;

class EventHandler {
public:
  EventHandler();
  ~EventHandler() = default;

  void RegisterCallback(lws_callback_reasons reason, CallbackHandler&& handler);
  void Execute(lws* wsi,
    const lws_callback_reasons reason,
    void* user_data,
    void* in,
    const size_t len);

private:
  MessageManager* mes_man_;
  CallbackMap cb_map_;
  uint64_t current_user_id_{ 0 };
};

}  // namespace ws

#endif  // !EVENT_HANDLER_H_
