#ifndef PAYLOAD_H_
#define PAYLOAD_H_

#include <cstdint>
#include <array>

namespace ws {

template<size_t N>
struct PayloadS {
  std::array<uint8_t, N> data{};
  size_t len{};
};

static constexpr auto kMaxDataSizeInBytes = 256;
using Payload = PayloadS<kMaxDataSizeInBytes>;

}  // namespace ws

#endif  // !PAYLOAD_H_