#include "vm.h"
#include "opcode_ids.h"
#include <vector>

//Читай примеры байт-кода в Examples/

int main() {
    std::vector<std::variant<int, std::string>> program = {
        LABEL, std::string("start"),
            PUSH, 0,          // Инициализация переменной i
        LABEL, std::string("loop"),
            DUP,              // Дублируем i
            PUSH, 10,
            CMP_LT, std::string("body"),   // Если i < 10, переходим к телу цикла
            HALT,
        LABEL, std::string("body"),
            DUP,
            PRINT,            // Выводим i
            PUSH, 1,
            ADD,              // Увеличиваем i на 1
            JUMP, std::string("loop"),     // Переход к началу цикла
    };


    VM vm;
    vm.execute(program);

    return 0;
}
