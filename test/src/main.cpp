#include <Hash.hpp>
#include <array>

int main() {

    std::array<u8, 32> data;
    data.fill(0);

    auto hash = blake3::Hash(data);

    std::cout << "Hello World!" << std::endl << hash.as_hex() << std::endl;

    return 0;
}