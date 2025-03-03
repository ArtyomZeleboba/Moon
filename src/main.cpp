#include "vm.hpp"
#include "opcode_ids.hpp"
#include <vector>

int main() {
    VM vm;

    // Байт-код для теста: (2 + 3) * (5 - 1) / 2
    std::vector<std::variant<int, std::string>> program = {
        RAND,
        PUSH, 1,
        PUSH, 0,
        SUB,
        INC,
        MOD,
        PUSH, 0,
        ADD,

        PRINT,
        HALT

    };

    vm.execute(program);

    return 0;
}
