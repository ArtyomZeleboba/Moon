# MoonVM 
Стековая виртуальная машина для интерпретаторов/компиляторов

# Как начать работу с машиной
**В первых версиях машины нету поддержки выполнения кода из файла, пока что только написание кода внутри машины и дальнейшая её компиляция вместе с машиной. А так-же отсутствует поддержка Windows, если вы опытный разработчик то можете скомпилировать всю машину самостоятельно без скрипта build.sh**

Логично что виртуальную машину нужно установить, это делается следующей командой:
```
git clone https://github.com/ArtyomBina/Moon.git
```

1. Откройте файл [```src/main.cpp```](src/main.cpp)

1.1 Если не знакомы с байт кодом Moon то [почитайте это](docs/bytecode.md)

2. Напишите необходимый вам байт код согласно примеру:
```cpp
#include "vm.h"
#include "opcode_ids.h"
#include <vector>

int main() {
	//Внутри переменной program напишите байт код, согласно документации(docs/bytecode.md)
    std::vector<std::variant<int, std::string>> program = {
        LABEL, std::string("start"),
            PUSH, 2,
            PRINT,
			 JUMP, std::string("end"),

        LABEL, std::string("end"),
            HALT
    };


    VM vm;
    vm.execute(program);

    return 0;
}
```

3. Запустите скрипт build.sh который скомпилирует виртуальную машину
4. На экране должен появится результат работы машины(если есть соответствующий опкод PRINT в байт коде)
