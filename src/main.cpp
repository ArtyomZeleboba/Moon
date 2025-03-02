#include "vm.h"
#include "opcode_ids.h"
#include <vector>

//Читай примеры байт-кода в Examples/

int main() {
    std::vector<std::variant<int, std::string>> program = {
        PUSH, 10,
        PUSH, 3,
        MOD,       // 10 % 3 = 1
        PRINT,     // Выведет 1
        HALT
    };


    VM vm;
    vm.execute(program);

    return 0;
}
