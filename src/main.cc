#include <libwebsockets.h>
#include "event_handler.h"
#include "per_session_data.h"
#include <csignal>

ws::EventHandler event_handler;

static int CallbackRtds(lws* wsi,
  const lws_callback_reasons reason,
  void* user_data,
  void* in,
  const size_t len) {
  event_handler.Execute(wsi, reason, user_data, in, len);
  return 0;
}

static struct lws_protocols g_proto_list[] = {
  /* first protocol must always be HTTP handler */
  {
    "http-only",              // name
    lws_callback_http_dummy,  // callback
    0                         // per_session_data_size
  },
  {
    "callback_rtds",            // protocol name - very important!
    CallbackRtds,               // callback
    sizeof(ws::PerSessionData)  // we don't use any per session data
  },
  { nullptr, nullptr, 0 /* End of list */ }
};

static int g_interruped;

void SignalHandler(int) {
  g_interruped = 1;
}

static const struct lws_http_mount mount = {
  /* .mount_next */ NULL,          /* linked-list "next" */
  /* .mountpoint */ "/",           /* mountpoint URL */
  /* .origin */ "../mount-origin", /* serve from dir */
  /* .def */ "index.html",         /* default filename */
  /* .protocol */ NULL,
  /* .cgienv */ NULL,
  /* .extra_mimetypes */ NULL,
  /* .interpret */ NULL,
  /* .cgi_timeout */ 0,
  /* .cache_max_age */ 0,
  /* .auth_mask */ 0,
  /* .cache_reusable */ 0,
  /* .cache_revalidate */ 0,
  /* .cache_intermediaries */ 0,
  /* .cache_no */ 0,
  /* .origin_protocol */ LWSMPRO_FILE, /* files in a dir */
  /* .mountpoint_len */ 1,             /* char count */
  /* .basic_auth_login_file */ NULL,
};

int main() {
  // register CTRL-C
  signal(SIGINT, SignalHandler);

  const auto port = 9000;
  const char* iface = nullptr;

  // we're not using ssl
  const char* cert_path = nullptr;
  const char* key_path = nullptr;

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
  ctx_info.mounts = &mount;
  ctx_info.vhost_name = "localhost";

  lws_set_log_level(LLL_ERR | LLL_WARN | LLL_NOTICE | LLL_INFO, nullptr);

  // create libwebsocket context representing this server
  const auto ctx = lws_create_context(&ctx_info);
  if (!ctx) {
    lwsl_err("Cannot create context. Quiting...\n");
    return -1;
  }

  lwsl_info("Server started!\n");

  // infinite loop, to end this server send SIGTERM. (CTRL+C)
  while (!g_interruped) {
    lws_service(ctx, 0);
  }

  lws_context_destroy(ctx);

  return 0;
}