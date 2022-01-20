#include "message_manager.h"
#include <libwebsockets.h>

namespace ws {

void MessageManager::CreateMessage(
  const uint64_t client_id, const void* data, const uint64_t len) {
  if (len > kMaxDataSizeInBytes) {
    lwsl_err("Invalid Data Size!\n");
    return;
  }
  Payload pl{ .len = len };
  memcpy(pl.data.data() + LWS_PRE, data, len);
  send_queue_->enqueue(client_id, pl);
}

void MessageManager::SendMessage(lws* wsi, const uint64_t client_id) {
  // get the message from the queue
  auto message_opt = send_queue_->dequeue(client_id);
  if (!message_opt.has_value()) {
    return;
  }

  if (!wsi) {
    lwsl_err("Client has disappeared!\n");
    return;
  }

  auto& message = message_opt.value();

  // write the message to the wire.
  const auto bytes_sent = lws_write(
    wsi, message.data.data() + LWS_PRE, message.len, LWS_WRITE_BINARY);

  // make sure that the whole message is sent
  if (bytes_sent < static_cast<int>(message.len)) {
    lwsl_err("ERROR %d writing to ws\n", bytes_sent);
  }
}

MessageManager* GetMessageManager(lws* wsi) {
  return static_cast<ws::MessageManager*>(
    lws_protocol_vh_priv_get(lws_get_vhost(wsi), lws_get_protocol(wsi)));
}

MessageManager* MessageManager::Create(lws* wsi) {
  auto man = static_cast<ws::MessageManager*>(lws_protocol_vh_priv_zalloc(
    lws_get_vhost(wsi), lws_get_protocol(wsi), sizeof(ws::MessageManager)));
  man->send_queue_ = new Queue;
  return man;
}

void MessageManager::Destroy(lws* wsi) {
  auto man = GetMessageManager(wsi);
  delete man->send_queue_;
}

}  // namespace ws
