#include "arithmetic_operations.hpp"
#include <cmath>
#include <cstdlib>  
#include <ctime>

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

void mod(std::stack<int>& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for this operation(MOD)");
    }
    int b = stack.top(); stack.pop();  // Второй операнд
    int a = stack.top(); stack.pop();  // Первый операнд

    stack.push(a % b);                 // Результат
}

void inc(std::stack<int>& stack) {
    if (stack.empty()) {
        throw std::runtime_error("Stack error: stack is empty for INC");
    }
    int value = stack.top(); stack.pop();
    stack.push(value + 1);
}
void dec(std::stack<int>& stack) {
    if (stack.empty()) {
        throw std::runtime_error("Stack error: stack is empty for DEC");
    }
    int value = stack.top(); stack.pop();
    stack.push(value - 1);
}
void neg(std::stack<int>& stack) {
    if (stack.empty()) {
        throw std::runtime_error("Stack error: stack is empty for NEG");
    }
    int value = stack.top(); stack.pop();
    stack.push(-value);  
}
void abs(std::stack<int>& stack) {
    if (stack.empty()) {
        throw std::runtime_error("Stack error: stack is empty for ABS");
    }
    int value = stack.top(); stack.pop();
    stack.push(value < 0 ? -value : value); 
}
void pow(std::stack<int>& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for POW");
    }
    int exponent = stack.top(); stack.pop();
    int base = stack.top(); stack.pop();
    int result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    stack.push(result); 
}

void sqrt(std::stack<int>& stack) {
    if (stack.empty()) {
        throw std::runtime_error("Stack error: stack is empty for SQRT");
    }
    int value = stack.top(); stack.pop();
    if (value < 0) {
        throw std::runtime_error("Math error: cannot compute square root of a negative number");
    }
    stack.push(static_cast<int>(std::sqrt(value)));
}
void min(std::stack<int>& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for MIN");
    }
    int b = stack.top(); stack.pop();
    int a = stack.top(); stack.pop();
    stack.push(a < b ? a : b);
}
void max(std::stack<int>& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for MAX");
    }
    int b = stack.top(); stack.pop();
    int a = stack.top(); stack.pop();
    stack.push(a > b ? a : b);
}
void avg(std::stack<int>& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for AVG");
    }
    int b = stack.top(); stack.pop();
    int a = stack.top(); stack.pop();
    stack.push((a + b) / 2);
}
void rand(std::stack<int>& stack) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    stack.push(std::rand());
}
