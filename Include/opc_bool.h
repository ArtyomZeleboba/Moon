#ifndef OPC_BOOL_H
#define OPC_BOOL_H

#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <variant>
#include <stdexcept>

void cmp_eq(std::stack<int>& stack, size_t& pc, std::vector<std::variant<int, std::string>>& program, std::map<int, size_t>& lineToIndex);
void cmp_ne(std::stack<int>& stack, size_t& pc, std::vector<std::variant<int, std::string>>& program, std::map<int, size_t>& lineToIndex);
void cmp_gt(std::stack<int>& stack, size_t& pc, std::vector<std::variant<int, std::string>>& program, std::map<int, size_t>& lineToIndex);
void cmp_lt(std::stack<int>& stack, size_t& pc, std::vector<std::variant<int, std::string>>& program, std::map<int, size_t>& lineToIndex);

void _and(std::stack<int>& stack);
void _or(std::stack<int>& stack);
void _not(std::stack<int>& stack);

#endif//OPC_BOOL_H
