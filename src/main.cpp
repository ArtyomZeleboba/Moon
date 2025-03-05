#include "vm.hpp"
#include "opcode_ids.hpp"
#include <vector>


int main(int argc, char* argv[]) {
    // Проверяем, передан ли аргумент с путём к файлу
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " <путь_к_файлу>" << std::endl;
        return 1;
    }

    // Открываем бинарный файл для чтения
    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Ошибка открытия файла: " << argv[1] << std::endl;
        return 1;
    }

    std::vector<std::variant<int, std::string>> data;

    while (file) {
        char marker;
        file.read(&marker, sizeof(marker));  // Читаем маркер

        if (file.eof()) break;  // Если файл закончился

        if (marker == '\x01') {  // Если это число
            int number;
            file.read(reinterpret_cast<char*>(&number), sizeof(number));
            data.push_back(number);
        } else if (marker == '\x02') {  // Если это строка
            std::string str;
            char ch;
            while (file.get(ch) && ch != '\0') {
                str += ch;
            }
            data.push_back(str);
        } else {
            std::cerr << "Неизвестный маркер в файле!" << std::endl;
            return 1;
        }
    }

    VM vm;
    vm.execute(data);

    return 0;
}
