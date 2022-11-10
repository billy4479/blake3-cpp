#pragma once

#include <array>
#include <blake3_bindings.h>
#include <span>
#include <string>

namespace blake3 {

class Hash {
    NON_COPYABLE(Hash)
    DEFAULT_MOVE(Hash)

  public:
    Hash(std::span<u8>);
    ~Hash();

    std::array<u8, 32> as_bytes();
    std::string as_hex();

  private:
    blake3_bindings::Hash *m_hash;
};

} // namespace blake3