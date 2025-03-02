#include "opc_bool.h"

void _and(std::stack<int>& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for AND");
    }
    int b = stack.top(); stack.pop();
    int a = stack.top(); stack.pop();
    stack.push(a && b ? 1 : 0);  // 1, если оба истинны, иначе 0  
}
void _or(std::stack<int>& stack) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for OR");
    }
    int b = stack.top(); stack.pop();
    int a = stack.top(); stack.pop();
    stack.push(a || b ? 1 : 0);  // 1, если хотя бы один истинен, иначе 0
}
void _not(std::stack<int>& stack) {
    if (stack.empty()) {
        throw std::runtime_error("Stack error: stack is empty for NOT");
    }
    int a = stack.top(); stack.pop();
    stack.push(!a ? 1 : 0);  // 1, если a == 0, иначе 0
}
