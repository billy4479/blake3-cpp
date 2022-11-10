#include "Hasher.hpp"

namespace blake3 {

Hasher::Hasher() { m_hasher = blake3_bindings::new_hasher(); }

Hasher::~Hasher() {
    blake3_bindings::free_hasher(m_hasher);
    m_hasher = nullptr;
}

void Hasher::update(std::span<u8> input) {
    blake3_bindings::hasher_update(m_hasher, input.data(), input.size());
}

void Hasher::update_multithreaded(std::span<u8> input) {
    blake3_bindings::hasher_update_rayon(m_hasher, input.data(), input.size());
}

void Hasher::reset() { blake3_bindings::hasher_reset(m_hasher); }

u64 Hasher::count() { return blake3_bindings::hasher_count(m_hasher); }

} // namespace blake3