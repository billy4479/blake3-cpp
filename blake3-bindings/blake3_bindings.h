#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>

namespace blake3_bindings {

struct Hash;

struct Hasher;

extern "C" {

Hash *hash(const uint8_t *data, uintptr_t length);

void free_hash(Hash *hash);

const uint8_t (*hash_as_bytes(const Hash *hash))[32];

const char *hash_as_hex(const Hash *hash);

Hasher *new_hasher();

void free_hasher(Hasher *hasher);

void hasher_update(Hasher *hasher, const uint8_t *data, uintptr_t length);

Hash *hasher_finalize(Hasher *hasher);

void hasher_reset(Hasher *hasher);

unsigned long long hasher_count(Hasher *hasher);

} // extern "C"

} // namespace blake3_bindings
