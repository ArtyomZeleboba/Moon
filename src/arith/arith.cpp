#include "arithmetic_operations.h"

void add(std::stack<int>& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for this operation(ADD)");
    }
    int b = stack.top(); stack.pop();  // Второй операнд
    int a = stack.top(); stack.pop();  // Первый операнд
    stack.push(a + b);                 // Результат
}

void sub(std::stack<int>& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for this operation(SUB)");
    }
    int b = stack.top(); stack.pop();  // Второй операнд
    int a = stack.top(); stack.pop();  // Первый операнд
    stack.push(a - b);                 // Результат
}

void mul(std::stack<int>& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for this operation(MUL)");
    }
    int b = stack.top(); stack.pop();  // Второй операнд
    int a = stack.top(); stack.pop();  // Первый операнд
    stack.push(a * b);                 // Результат
}

void div(std::stack<int>& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for this operation(DIV)");
    }
    int b = stack.top(); stack.pop();  // Второй операнд
    int a = stack.top(); stack.pop();  // Первый операнд
    if (b == 0) {
        throw std::runtime_error("Division by zero");
    }
    stack.push(a / b);                 // Результат
}
