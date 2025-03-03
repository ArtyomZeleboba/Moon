#include "vm.hpp"
#include "opcode_ids.hpp"
#include <vector>

int main() {
    VM vm;

    // Байт-код для теста: (2 + 3) * (5 - 1) / 2
    std::vector<std::variant<int, std::string>> program = {
        RAND,
        PRINT,
        HALT
    };

    vm.execute(program);

    return 0;
}
