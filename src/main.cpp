#include <libwebsockets.h>
#include <cassert>
#include <csignal>
#include <cstring>
#include <string>
#include "data.hpp"

static int CallbackHttp(lws *wsi, const lws_callback_reasons reason, void *user_data, void *in, const size_t len)
{
  return 0;
}

static uint64_t current_user_id = 0;

static inline std::string create_message(const uint64_t id)
{
  static char buffer[20];
  const auto pos = sprintf(buffer, "message for: %lu", id);
  return {buffer, buffer + pos};
}

static int CallbackRtds(lws *wsi, const lws_callback_reasons reason, void *user_data, void *in, const size_t len)
{
  const auto pss = static_cast<PerSessionData *>(user_data);
  auto vhd = static_cast<PerVHostData *>(lws_protocol_vh_priv_get(lws_get_vhost(wsi), lws_get_protocol(wsi)));

  switch (reason)
  {
  case LWS_CALLBACK_PROTOCOL_INIT:
    vhd = static_cast<PerVHostData *>(lws_protocol_vh_priv_zalloc(lws_get_vhost(wsi), lws_get_protocol(wsi), sizeof(PerVHostData)));
    vhd->send_queue_ = new QueueWithId<Buffer, std::mutex>;
    break;
  case LWS_CALLBACK_PROTOCOL_DESTROY:
    delete vhd->send_queue_;
    break;
  case LWS_CALLBACK_ESTABLISHED:
    pss->id = current_user_id++;
    pss->wsi = wsi;
    lws_set_timer_usecs(wsi, 1 * LWS_USEC_PER_SEC);
    break;
  case LWS_CALLBACK_TIMER:
  {
    const auto mes = create_message(pss->id);
    Buffer buf{};
    memcpy(buf.data.data() + LWS_PRE, mes.c_str(), mes.size());
    buf.len = mes.size();
    vhd->CreateMessage(buf, pss->id);
    lws_callback_on_writable(wsi);
    lws_set_timer_usecs(wsi, 1 * LWS_USEC_PER_SEC);
  }
  break;
  case LWS_CALLBACK_SERVER_WRITEABLE:
    vhd->SendMessage(wsi, pss->id);
    break;
  case LWS_CALLBACK_CLOSED:
    printf("connection closed\n");
    fflush(stdout);
    break;
  case LWS_CALLBACK_RECEIVE:
    printf("received: %s\n", (char *)in);
    fflush(stdout);
    break;
  default:
    printf("reason: %d\n", reason);
    fflush(stdout);
    break;
  }

  return 0;
}

static struct lws_protocols g_proto_list[] = {
    /* first protocol must always be HTTP handler */
    {
        "http-only",  // name
        CallbackHttp, // callback
        0             // per_session_data_size
    },
    {
        "callback_rtds",       // protocol name - very important!
        CallbackRtds,          // callback
        sizeof(PerSessionData) // we don't use any per session data
    },
    {nullptr, nullptr, 0 /* End of list */}};

static int g_interruped;

void SignalHandler(int)
{
  g_interruped = 1;
}

int main()
{
  // register CTRL-C
  signal(SIGINT, SignalHandler);

  const auto port = 9000;
  const char *iface = nullptr;

  // we're not using ssl
  const char *cert_path = nullptr;
  const char *key_path = nullptr;

  // no special options
  const auto opts = 0;

  lws_context_creation_info ctx_info{};
  ctx_info.port = port;
  ctx_info.iface = iface;
  ctx_info.protocols = g_proto_list;
  ctx_info.client_ssl_cert_filepath = cert_path;
  ctx_info.client_ssl_private_key_filepath = key_path;
  ctx_info.gid = -1;
  ctx_info.uid = -1;
  ctx_info.options = opts;

  lws_set_log_level(LLL_DEBUG, nullptr);

  // create libwebsocket context representing this server
  const auto ctx = lws_create_context(&ctx_info);
  assert(ctx);

  printf("starting server...\n");

  // infinite loop, to end this server send SIGTERM. (CTRL+C)
  while (!g_interruped)
  {
    lws_service(ctx, 0);
  }

  lws_context_destroy(ctx);

  return 0;
}