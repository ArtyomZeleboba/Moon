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
#include <cstdint>
#include <fstream>

class VM {
    public:
        // Публичные методы
        void execute(std::vector<std::variant<int, std::string>>& program);
        void analyzeLabels(std::vector<std::variant<int, std::string>>& program);

    private:
        // Внутренние данные
        std::stack<int> stack;  // Стек для промежуточных значений
        std::map<int, int> globalsV; // Глобальные переменные
        std::stack<int> lastPC;  // Последнее место управления (для JUMP_RET)
        std::map<int, std::vector<int>> memory; // Память
        std::map<std::string, int> labels; // Карта меток
        int nextAddress = 0; // Следующий адрес для памяти
        size_t pc = 0;   // Программный счетчик (место в байт-коде)

        // Приватные методы для выполнения команд
        void executeArithmeticOperation(int command, std::stack<int>& stack);
        void executeJumpOperation(int command, std::vector<std::variant<int, std::string>>& program, size_t& pc, const std::map<int, size_t>& lineToIndex, std::stack<int>& stack);
        void executeMemoryOperation(int command, std::vector<std::variant<int, std::string>>& program, size_t& pc, std::stack<int>& stack, std::map<int, std::vector<int>>& memory, int& nextAddress);
        void executeStackOperation(int command, std::stack<int>& stack);
        void executeComparisonOperation(int command, std::stack<int>& stack, size_t& pc, std::vector<std::variant<int, std::string>>& program, const std::map<int, size_t>& lineToIndex);
        void executeLogicalOperation(int command, std::stack<int>& stack);

        // Вспомогательные методы
        std::map<int, size_t> createLineToIndexMapping(const std::vector<std::variant<int, std::string>>& program) const;

};

#endif // VM_H
