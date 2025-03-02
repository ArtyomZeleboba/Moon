#include "vm.h"
#include "opcode_ids.h"
#include <vector>

//Читай примеры байт-кода в Examples/

int main() {
    std::vector<std::variant<int, std::string>> program = {
        LABEL, std::string("start"),
            PUSH, 1,
            PUSH, 9,
            CMP_EQ, std::string("if_block"),
            JUMP, std::string("else_block"),

        LABEL, std::string("if_block"),
            PUSH, 4,
            PRINT,
            JUMP, std::string("end"),
        LABEL, std::string("else_block"),
            PUSH, 18,
            PRINT,
        LABEL, std::string("end"),
            HALT
    };


    VM vm;
    vm.execute(program);

    return 0;
}
