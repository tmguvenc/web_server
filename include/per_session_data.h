#ifndef PER_SESSION_DATA_H_
#define PER_SESSION_DATA_H_

#include <cstdint>
#include "common.h"

struct lws;

namespace ws {

struct PerSessionData {
  lws* wsi;
  uint64_t id;
  ClientRequestMessage req_mes_{};
};

}  // namespace ws

#endif  // !PER_SESSION_DATA_H_
