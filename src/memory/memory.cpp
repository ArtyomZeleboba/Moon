#include "memory.hpp"

void alloc(std::stack<int>& stack, std::map<int, std::vector<int>>& memory, int& nextAddress) {
    int size = stack.top(); stack.pop();
    int address = nextAddress++;
    memory[address] = std::vector<int>(size);
    stack.push(address); 
}

void store_mem(std::stack<int>& stack, std::map<int, std::vector<int>>& memory) {
    int value = stack.top(); stack.pop();
    int index = stack.top(); stack.pop();
    int address = stack.top(); stack.pop();

    if (memory.find(address) == memory.end()) {
        throw std::runtime_error("[STORE MEM] Memory address not found");
    }
    if (index < 0 || index >= memory[address].size()) {
        throw std::runtime_error("[STORE MEM] Memory index out of bounds");
    }

    memory[address][index] = value; 
}

void load_mem(std::stack<int>& stack, std::map<int, std::vector<int>>& memory) {
    int index = stack.top(); stack.pop();
    int address = stack.top(); stack.pop();

    if (memory.find(address) == memory.end()) {
        throw std::runtime_error("[LOAD MEM] Memory address not found");
    }
    if (index < 0 || index >= memory[address].size()) {
        throw std::runtime_error("[LOAD MEM] Memory index out of bounds");
    }

    stack.push(memory[address][index]); 
}

void free(std::stack<int>& stack, std::map<int, std::vector<int>>& memory) {
    int address = stack.top(); stack.pop();

    if (memory.find(address) == memory.end()) {
        throw std::runtime_error("[FREE] Memory address not found");
    }

    memory.erase(address); 
}
