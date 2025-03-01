#include "stack.h"

void push(std::vector<std::variant<int, std::string>>& program, size_t& pc, std::stack<int>& stack) {
    int operand = std::get<int>(program[++pc]);  // Получаем значение
    stack.push(operand);      
}
void pop(std::stack<int>& stack) {
    stack.pop(); 
}
void dup(std::stack<int>& stack) {
    if (stack.empty()) {
        throw std::runtime_error("Stack error: stack is empty for DUP");
    }
    int value = stack.top();
    stack.push(value);  // Дублируем верхний элемент 
}
void swap(std::stack<int>& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for SWAP");
    }
    int a = stack.top(); stack.pop();
    int b = stack.top(); stack.pop();
    stack.push(a);
    stack.push(b);  // Меняем местами два верхних элемента
}
