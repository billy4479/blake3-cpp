#pragma once

#include <blake3_bindings.h>
#include <span>

namespace blake3 {

class Hasher {
    NON_COPYABLE(Hasher)
    DEFAULT_MOVE(Hasher)

  public:
    Hasher();
    ~Hasher();

    void update(std::span<u8>);
    void reset();
    u64 count();

  private:
    blake3_bindings::Hasher *m_hasher{nullptr};
};

} // namespace blake3