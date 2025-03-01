#ifndef VM_H
#define VM_H

#include <stack>
#include <vector>
#include <map>
#include <stdexcept>
#include <string>
#include <variant>
#include <iostream>
#include <unordered_map>


struct VM {
    std::stack<int> stack;  // Стек для промежуточных значений
    std::map<int, int> globalsV; //Глобальные переменные
    std::stack<int> lastPC;  //Последнее место управления(для JUMP_RET)
    std::map<int, std::vector<int>> memory; //Память
    std::map<std::string, int> labels; //Карта лэйблов
    int nextAddress = 0; //Следущий адрес для памяти
    size_t pc = 0;   // Место в байт коде

    void execute(std::vector<std::variant<int, std::string>>& program);
    void analyze_Labels(std::vector<std::variant<int, std::string>>& program);
};

#endif // VM_H
