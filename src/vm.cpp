#include "opcode_ids.h"
#include "arithmetic_operations.h"
#include "jump_operations.h"
#include "memory.h"
#include "stack.h"
#include "opc_bool.h"

#include "vm.h"

//База хранящая информацию есть ли у опкода аргумент или нет
namespace {
    const std::unordered_map<int, int> COMMAND_ARGS = {
        {PUSH, 1}, {POP, 0}, {ADD, 0}, {SUB, 0}, {MUL, 0}, {DIV, 0},
        {PRINT, 0}, {HALT, 0}, {STORE_GLOBAL, 1}, {LOAD_GLOBAL, 1},
        {ALLOC, 0}, {STORE_MEM, 0}, {LOAD_MEM, 0}, {FREE, 0},
        {JUMP, 1}, {JUMPIZ, 1}, {JUMPINZ, 1}, {LABEL, 1},
        {JUMP_RET, 1}, {JUMPIZ_RET, 1}, {JUMPINZ_RET, 1},
        {DUP, 0}, {SWAP, 0}, {CMP_EQ, 1}, {CMP_NE, 1},
        {CMP_GT, 1}, {CMP_LT, 1}, {AND, 0}, {OR, 0}, {NOT, 0}
    };
}

std::map<int, size_t> createLineToIndexMapping(const std::vector<std::variant<int, std::string>>& program) {
    std::map<int, size_t> lineToIndex;
    size_t index = 0;
    int lineNumber = 1;

    while (index < program.size()) {
        lineToIndex[lineNumber] = index; // Текущая область кода
        const auto& cmd = program[index]; // Получаем текущую команду
        
        if (!std::holds_alternative<int>(cmd)) { // Если опкод не число то кидаем рантайм эррор
            throw std::runtime_error("Invalid command type");
        }

        const int opcode = std::get<int>(cmd); //Получаем опкод как число
        const auto it = COMMAND_ARGS.find(opcode); //Смотрим есть ли такой опкод в базе COMMAND_ARGS
        if (it == COMMAND_ARGS.end()) { // Если нет кидаем ошибку
            throw std::runtime_error("Unknown opcode: " + std::to_string(opcode));
        }

        index += 1 + it->second; //Приссоединяем индекс на начало следущей инструкции
        lineNumber++; //Следущая область кода
    }

    return lineToIndex; //Возвращаем карту областей с индексами
}

void VM::analyze_Labels(std::vector<std::variant<int, std::string>>& program) {
    size_t index = 0;
    int current_line = 1;
    int count_labels = 0;
    std::map<int, size_t> lineToIndex = createLineToIndexMapping(program);
    std::vector<std::variant<int, std::string>> result_programm;

    while (index < program.size()) {
        const auto& instruction = program[index];
        if (std::holds_alternative<int>(instruction)) {
            int command = std::get<int>(instruction);

            if (command == LABEL) {
                count_labels++;
                if (index + 1 >= program.size()) {
                    throw std::runtime_error("Unexpected end of program");
                }
                const auto& label = program[++index];
                if (std::holds_alternative<std::string>(label)) {
                    std::string name_label = std::get<std::string>(label);
                    for (const auto& pair : lineToIndex) {
                        if (pair.second == index - 1) {
                            current_line = pair.first;
                            break;
                        }
                    }
                    labels[name_label] = (current_line - count_labels) + 1;
                } else {
                    throw std::runtime_error("Expected label name (string), but found an integer");
                }
            } else {
                result_programm.push_back(command);
                const auto it = COMMAND_ARGS.find(command);
                if (it != COMMAND_ARGS.end() && it->second == 1) {
                    if (index + 1 >= program.size()) {
                        throw std::runtime_error("Unexpected end of program");
                    }
                    result_programm.push_back(program[++index]);
                }
            }
        } else {
            result_programm.push_back(std::get<std::string>(instruction));
        }
        index++;
    }

    // Второй проход: замена меток на индексы
    index = 0;
    std::vector<std::variant<int, std::string>> final_programm;
    while (index < result_programm.size()) {
        const auto& instruction = result_programm[index];
        if (std::holds_alternative<int>(instruction)) {
            int command = std::get<int>(instruction);

            if (command == JUMP || command == JUMPIZ || command == JUMPINZ ||
                command == JUMP_RET || command == JUMPIZ_RET || command == JUMPINZ_RET || 
                command == CMP_EQ || command == CMP_NE || command == CMP_GT || command == CMP_LT) {

                final_programm.push_back(command);
                if (index + 1 >= result_programm.size()) {
                    throw std::runtime_error("Unexpected end of program");
                }
                const auto& label = result_programm[++index];
                if (std::holds_alternative<std::string>(label)) {
                    std::string name_label = std::get<std::string>(label);
                    final_programm.push_back(labels[name_label]);
                } else {
                    final_programm.push_back(std::get<int>(label));
                }
            } else {
                final_programm.push_back(command);
                const auto it = COMMAND_ARGS.find(command);
                if (it != COMMAND_ARGS.end() && it->second == 1) {
                    if (index + 1 >= result_programm.size()) {
                        throw std::runtime_error("Unexpected end of program");
                    }
                    final_programm.push_back(result_programm[++index]);
                }
            }
        } else {
            final_programm.push_back(std::get<std::string>(instruction));
        }
        index++;
    }

    // Обновление программы и PC
    program = std::move(final_programm);
    lineToIndex = createLineToIndexMapping(program);
    if (labels.find("start") == labels.end()) {
        pc = 0;
    } else {
        pc = lineToIndex[labels["start"]];
    }
}

void VM::execute(std::vector<std::variant<int, std::string>>& program) {
    this->analyze_Labels(program);
    std::map<int, size_t> lineToIndex = createLineToIndexMapping(program);

    while (pc < program.size()) {
        const auto& instruction = program[pc];
    

        // Проверяем, является ли instruction числом (командой)
        if (std::holds_alternative<int>(instruction)) {
            int command = std::get<int>(instruction);

            if (command == PUSH) {
                push(program, pc, stack);
            } else if (command == POP) {
                pop(stack);
            } else if (command == DUP) {
                dup(stack);
            } else if (command == SWAP) {
                swap(stack);
            } else if (command == ADD) {
                add(stack);
            } else if (command == SUB) {
                sub(stack);
            } else if (command == MUL) {
                mul(stack);
            } else if (command == DIV) {
                div(stack);
            } else if (command == PRINT) {
                if (stack.empty()) {
                    throw std::runtime_error("Stack error: stack is empty for PRINT");
                }
                std::cout <<  stack.top() << std::endl;  // Вывод верхнего элемента
                stack.pop();
            } else if (command == STORE_GLOBAL) {
                int address = std::get<int>(program[++pc]); // Получаем адрес для сохранения переменной
                int value = stack.top(); stack.pop(); // Так как перед сохранением мы сделали push, то достаём из вершины стека
                globalsV[address] = value; // В map сохраняем значение переменной
                std::cout<<"f"<<globalsV[address]<<std::endl; 
            } else if (command == LOAD_GLOBAL) {
                int address = std::get<int>(program[++pc]); // Получаем адрес переменной
                
                if (globalsV.find(address) == globalsV.end()) {
                    throw std::runtime_error("[LOAD GLOBAL] Global variable not found");
                }
                stack.push(globalsV[address]); // Помещаем в стек то, что вытащили
            } else if (command == ALLOC) {
                alloc(stack, memory, nextAddress);
            } else if (command == STORE_MEM) {
                store_mem(stack, memory);
            } else if (command == LOAD_MEM) {
                load_mem(stack, memory);
            } else if (command == FREE) {
                free(stack, memory);
            } else if (command == JUMP) {
                jump(program, pc, lineToIndex);
            } else if (command == JUMPIZ) {
                jumpiz(program, pc, stack, lineToIndex);
            } else if (command == JUMPINZ) {
                jumpinz(program, pc, stack, lineToIndex);
            } else if (command == JUMP_RET) {
                lastPC.push(pc);
                jump(program, pc, lineToIndex);
            } else if (command == JUMPIZ_RET) {
                lastPC.push(pc);
                jumpiz(program, pc, stack, lineToIndex);
            } else if (command == JUMPINZ_RET) {
                lastPC.push(pc);
                jumpinz(program, pc, stack, lineToIndex);
            } else if (command == CMP_EQ) {
                cmp_eq(stack, pc, program, lineToIndex);
            } else if (command == CMP_NE) {
                cmp_ne(stack, pc, program, lineToIndex);
            } else if (command == CMP_GT) {
                cmp_gt(stack, pc, program, lineToIndex);
            } else if (command == CMP_LT) {
                cmp_lt(stack, pc, program, lineToIndex);
            } else if (command == AND) {
                and(stack);
            } else if (command == OR) {
                or(stack);
            } else if (command == NOT) {
                _not(stack);
            } else if (command == HALT) {
                return;  // Завершение программы
            } else if (command == LABEL) {
                pc += 2;
            } else {
                throw std::runtime_error("Unknown instruction");
            }
        } else {
            throw std::runtime_error("Expected command but found a string");
        }

        pc++;  // Переход к следующей команде
    }

    if (!lastPC.empty()) {
        this->pc = lastPC.top();
        lastPC.pop();
        pc += 2;
        this->execute(program);
    }
}



