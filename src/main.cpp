#include "MyClass.hpp"

int main() {
    MyClass my_class(42);

    std::cout << "Hello World!" << std::endl
              << my_class.get_my_number() << std::endl;

    return 0;
}