#ifndef ARITHMETIC_OPERATIONS_H
#define ARITHMETIC_OPERATIONS_H

#include <stack>
#include <stdexcept>

void add(std::stack<int>& stack);
void sub(std::stack<int>& stack);
void mul(std::stack<int>& stack);
void div(std::stack<int>& stack);
void mod(std::stack<int>& stack);

void inc(std::stack<int>& stack);
void dec(std::stack<int>& stack);
void neg(std::stack<int>& stack);
void abs(std::stack<int>& stack);
void pow(std::stack<int>& stack);

void sqrt(std::stack<int>& stack);
void min(std::stack<int>& stack);
void max(std::stack<int>& stack);
void avg(std::stack<int>& stack);
void rand(std::stack<int>& stack);

#endif // ARITHMETIC_OPERATIONS_H
