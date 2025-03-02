#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <stdexcept>

void alloc(std::stack<int>& stack, std::map<int, std::vector<int>>& memory, int& address);

void store_mem(std::stack<int>& stack, std::map<int, std::vector<int>>& memory);

void load_mem(std::stack<int>& stack, std::map<int, std::vector<int>>& memory);

void free(std::stack<int>& stack, std::map<int, std::vector<int>>& memory);


#endif //MEMORY_H
