#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
#include <variant>
#include <stack>
#include <stdexcept>

void push(std::vector<std::variant<int, std::string>>& program, size_t& pc, std::stack<int>& stack);
void pop(std::stack<int>& stack);
void dup(std::stack<int>& stack);
void swap(std::stack<int>& stack);

#endif //STACK_H

