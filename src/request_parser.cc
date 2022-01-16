#include "request_parser.h"
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <libwebsockets.h>
#include "common.h"

namespace ws {

using namespace boost::property_tree;

std::optional<ClientRequestMessage> ParseClientMessage(
  const void* in, const size_t len) {
  if (in == nullptr || len == 0) {
    lwsl_err("received invalid message\n");
    return {};
  }

  ptree pt{};
  std::stringstream ss;
  ss.write(static_cast<const char*>(in), len);
  lwsl_info("received msg: %s\n", ss.str().c_str());

  json_parser::read_json(ss, pt);
  if (!json_parser::verify_json(pt, 3)) {
    lwsl_err("received invalid json\n");
    return {};
  }

  ClientRequestMessage client_mes;
  client_mes.device_name = pt.get<std::string>("msg");
  return client_mes;
}

}  // namespace ws
