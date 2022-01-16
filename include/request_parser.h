#ifndef REQUEST_PARSER_H_
#define REQUEST_PARSER_H_

#include <optional>
#include "common.h"

namespace ws {

std::optional<ClientRequestMessage> ParseClientMessage(
  const void* in, const size_t len);

}  // namespace ws

#endif  // !REQUEST_PARSER_H_
