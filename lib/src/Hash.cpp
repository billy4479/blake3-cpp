#include "Hash.hpp"

namespace blake3 {

Hash::Hash(std::span<u8> input) {
    m_hash = blake3_bindings::hash(input.data(), input.size());
}

Hash::~Hash() { blake3_bindings::free_hash(m_hash); }

std::array<u8, 32> Hash::as_bytes() {
    auto out = *blake3_bindings::hash_as_bytes(m_hash);
    auto arr = std::array<u8, 32>();

    for (size_t i = 0; i < 32; ++i)
        arr[i] = out[i];

    delete[] out;
    return arr;
}

std::string Hash::as_hex() {
    auto ptr = blake3_bindings::hash_as_hex(m_hash);
    auto str = std::string(ptr);
    free((void *)ptr);
    return str;
}

} // namespace blake3