#include "vm.h"
#include "opcode_ids.h"
#include <vector>

int main() {
    std::vector<std::variant<int, std::string>> program = {
        LABEL, std::string(".cmp_eq"),
            PUSH, 1,
            PUSH, 3,
            SWAP,
            PRINT,
            PRINT,
            JUMP, std::string("end"),
        
        LABEL, std::string("start"),
            PUSH, 120,
            PUSH, 120,
            CMP_GT, std::string(".cmp_eq"),
        
        LABEL, std::string("end"),
            HALT
    };


    VM vm;
    vm.execute(program);

    return 0;
}
