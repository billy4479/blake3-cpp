#include "MyClass.hpp"
#include <blake3.h>

int main() {
    MyClass my_class(42);

    std::cout << "Hello World!" << std::endl
              << add(my_class.get_my_number(), my_class.get_my_number())
              << std::endl;

    return 0;
}