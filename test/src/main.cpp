#include <Hash.hpp>
#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <vector>

int main(i32 argc, char **argv) {

    if (argc != 2)
        exit(1);

    namespace fs = std::filesystem;

    auto path = fs::path(argv[1]);
    auto file = std::ifstream(path, std::ios::in | std::ios::binary);
    auto vec = std::vector<u8>((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());

    auto hash = blake3::Hash(vec);
    std::cout << hash.as_hex() << std::endl;

    return 0;
}