#include "opc_bool.hpp"

void cmp_eq(std::stack<int>& stack, size_t& pc, std::vector<std::variant<int, std::string>>& program, const std::map<int, size_t>& lineToIndex) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for CMP_EQ");
    }
    int b = stack.top(); stack.pop();
    int a = stack.top(); stack.pop();
    
    int lineNumber = std::get<int>(program[++pc]);
    
    if (lineToIndex.find(lineNumber) == lineToIndex.end()) {
        throw std::runtime_error("Invalid line number for CMP_EQ");
    }
    
    if (a == b)
        pc = lineToIndex.at(lineNumber) - 1;
}

void cmp_ne(std::stack<int>& stack, size_t& pc, std::vector<std::variant<int, std::string>>& program, const std::map<int, size_t>& lineToIndex) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for CMP_EQ");
    }
    int b = stack.top(); stack.pop();
    int a = stack.top(); stack.pop();
    
    int lineNumber = std::get<int>(program[++pc]);
    
    if (lineToIndex.find(lineNumber) == lineToIndex.end()) {
        throw std::runtime_error("Invalid line number for CMP_EQ");
    }
    
    if (a != b)
        pc = lineToIndex.at(lineNumber) - 1;
}

void cmp_gt(std::stack<int>& stack, size_t& pc, std::vector<std::variant<int, std::string>>& program, const std::map<int, size_t>& lineToIndex) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for CMP_EQ");
    }
    int b = stack.top(); stack.pop();
    int a = stack.top(); stack.pop();
    
    int lineNumber = std::get<int>(program[++pc]);
    
    if (lineToIndex.find(lineNumber) == lineToIndex.end()) {
        throw std::runtime_error("Invalid line number for CMP_EQ");
    }
    
    if (a > b)
        pc = lineToIndex.at(lineNumber) - 1;
}

void cmp_lt(std::stack<int>& stack, size_t& pc, std::vector<std::variant<int, std::string>>& program, const std::map<int, size_t>& lineToIndex) {
    if (stack.size() < 2) {
        throw std::runtime_error("Stack error: two operands missing for CMP_EQ");
    }
    int b = stack.top(); stack.pop();
    int a = stack.top(); stack.pop();
    
    int lineNumber = std::get<int>(program[++pc]);
    
    if (lineToIndex.find(lineNumber) == lineToIndex.end()) {
        throw std::runtime_error("Invalid line number for CMP_EQ");
    }
    
    if (a < b)
        pc = lineToIndex.at(lineNumber) - 1;
}
