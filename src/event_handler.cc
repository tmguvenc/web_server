#include "event_handler.h"
#include "per_session_data.h"
#include "message_manager.h"
#include "request_parser.h"
#include <random>
#include <string>
#include "rtds.pb.h"

std::random_device dev;
std::mt19937_64 rng(dev());
std::uniform_int_distribution<std::mt19937_64::result_type> dist(1, 100);

static inline std::string create_message(const uint64_t id) {
  const auto number = dist(rng);
  static char buffer[20];
  const auto pos = sprintf(buffer, "%lu", number);
  return { buffer, buffer + pos };
}

namespace ws {

static constexpr auto kTimeoutUs = 50 * 1000;

EventHandler::EventHandler() {
  RegisterCallback(LWS_CALLBACK_PROTOCOL_INIT,
    [&](lws* wsi, const lws_callback_reasons reason, void* user_data, void* in,
      const size_t len) { mes_man_ = MessageManager::Create(wsi); });

  RegisterCallback(LWS_CALLBACK_PROTOCOL_DESTROY,
    [&](lws* wsi, const lws_callback_reasons reason, void* user_data, void* in,
      const size_t len) { MessageManager::Destroy(wsi); });

  RegisterCallback(LWS_CALLBACK_CLOSED,
    [&](lws* wsi, const lws_callback_reasons reason, void* user_data, void* in,
      const size_t len) { --current_user_id_; });

  RegisterCallback(
    LWS_CALLBACK_ESTABLISHED, [&](lws* wsi, const lws_callback_reasons reason,
                                void* user_data, void* in, const size_t len) {
      const auto pss = static_cast<PerSessionData*>(user_data);
      pss->id = current_user_id_++;
      pss->wsi = wsi;
    });

  RegisterCallback(
    LWS_CALLBACK_TIMER, [&](lws* wsi, const lws_callback_reasons reason,
                          void* user_data, void* in, const size_t len) {
      const auto pss = static_cast<PerSessionData*>(user_data);
      const auto mes = create_message(pss->id);
      mes_man_->CreateMessage(pss->id, mes.c_str(), mes.size());
      lws_callback_on_writable(wsi);
      lws_set_timer_usecs(wsi, kTimeoutUs);
    });

  RegisterCallback(LWS_CALLBACK_SERVER_WRITEABLE,
    [&](lws* wsi, const lws_callback_reasons reason, void* user_data, void* in,
      const size_t len) {
      const auto pss = static_cast<PerSessionData*>(user_data);
      mes_man_->SendMessage(wsi, pss->id);
    });

  RegisterCallback(
    LWS_CALLBACK_RECEIVE, [&](lws* wsi, const lws_callback_reasons reason,
                            void* user_data, void* in, const size_t len) {
      const auto pss = static_cast<PerSessionData*>(user_data);
      MessageField mf;
      if (mf.ParseFromArray(in, len)) {
        lwsl_info("Message from [%s]: %f", mf.name().c_str(), mf.value());
      }

      // if (const auto ret = ParseClientMessage(in, len); ret.has_value()) {
      //   pss->req_mes_ = ret.value();
      // }

      lws_set_timer_usecs(wsi, kTimeoutUs);
    });
}

void EventHandler::RegisterCallback(
  lws_callback_reasons reason, CallbackHandler&& handler) {
  if (const auto it = cb_map_.find(reason); it != cb_map_.end()) {
    lwsl_err("Callback is already registered for [%d]\n", reason);
    return;
  }
  cb_map_[reason] = handler;
}

void EventHandler::Execute(lws* wsi,
  const lws_callback_reasons reason,
  void* user_data,
  void* in,
  const size_t len) {
  if (auto it = cb_map_.find(reason); it == cb_map_.end()) {
    lwsl_err("Callback not found for [%d]\n", reason);
  } else {
    it->second(wsi, reason, user_data, in, len);
  }
}

}  // namespace ws
