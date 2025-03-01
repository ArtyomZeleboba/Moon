#include "jump_operations.h"

void jump(std::vector<std::variant<int, std::string>>& program, size_t& pc, const std::map<int, size_t>& lineToIndex) {
    // Извлекаем номер строки для перехода
    int lineNumber = std::get<int>(program[++pc]);  

    if (lineToIndex.find(lineNumber) == lineToIndex.end()) {
        throw std::runtime_error("Invalid line number for JUMP");
    }
    pc = lineToIndex.at(lineNumber) - 1;  // Устанавливаем счётчик команд
}

void jumpiz(std::vector<std::variant<int, std::string>>& program, size_t& pc, std::stack<int>& stack, const std::map<int, size_t>& lineToIndex) {
    // Извлекаем номер строки для перехода
    int lineNumber = std::get<int>(program[++pc]);  
    int value = stack.top(); stack.pop();  // Значение с вершины стека
    if (value == 0) {
        if (lineToIndex.find(lineNumber) == lineToIndex.end()) {
            throw std::runtime_error("Invalid line number for JUMPIZ");
        }
        pc = lineToIndex.at(lineNumber) - 1;  // Переход, если значение равно 0
    }
}

void jumpinz(std::vector<std::variant<int, std::string>>& program, size_t& pc, std::stack<int>& stack, const std::map<int, size_t>& lineToIndex) {
    // Извлекаем номер строки для перехода
    int lineNumber = std::get<int>(program[++pc]);  
    int value = stack.top(); stack.pop();  // Значение с вершины стека
    if (value != 0) {
        if (lineToIndex.find(lineNumber) == lineToIndex.end()) {
            throw std::runtime_error("Invalid line number for JUMPINZ");
        }
        pc = lineToIndex.at(lineNumber) - 1;  // Переход, если значение не равно 0
    }
}
