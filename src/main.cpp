#include "MyClass.hpp"
#include <array>
#include <blake3.h>

int main() {

    std::array<u8, 32> data;
    data.fill(0);

    auto h = blake3_bindings::hash(data.data(), data.size());
    auto b = blake3_bindings::hash_as_hex(h);

    MyClass my_class(42);

    std::cout << "Hello World!" << std::endl << b << std::endl;

    return 0;
}