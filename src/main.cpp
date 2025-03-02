#include "vm.hpp"
#include "opcode_ids.hpp"
#include <vector>

int main() {
    VM vm;

    // Байт-код для теста: (2 + 3) * (5 - 1) / 2
    std::vector<std::variant<int, std::string>> program = {
        PUSH, 2,
        PUSH, 3,
        ADD,
        PUSH, 5,
        PUSH, 1,
        SUB,
        MUL,
        PUSH, 2,
        DIV,
        PRINT,
        HALT
    };

    vm.execute(program);

    return 0;
}
