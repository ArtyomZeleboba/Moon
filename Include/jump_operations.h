#ifndef JUMP_OPERATIONS_H
#define JUMP_OPERATIONS_H 

#include <stack>
#include <iostream>
#include <vector>
#include <map>
#include <variant>

void jump(std::vector<std::variant<int, std::string>>& program, size_t& pc,  const std::map<int, size_t>& lineToIndex);
void jumpiz(std::vector<std::variant<int, std::string>>& program, size_t& pc, std::stack<int>& stack,  const std::map<int, size_t>& lineToIndex);
void jumpinz(std::vector<std::variant<int, std::string>>& program, size_t& pc, std::stack<int>& stack,  const std::map<int, size_t>& lineToIndex);

#endif // JUMP_OPERATIONS_H
