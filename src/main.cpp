#include "MyClass.hpp"
#include <array>
#include <blake3.h>

int main() {

    std::array<u8, 32> data;
    data.fill(0);

    auto h = blake3::hash(data.data(), data.size());
    (void)h;

    MyClass my_class(42);

    std::cout << "Hello World!" << std::endl
              << blake3::add(my_class.get_my_number(), my_class.get_my_number())
              << std::endl;

    return 0;
}