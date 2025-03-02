#include "opcode_ids.hpp"
#include "arithmetic_operations.hpp"
#include "jump_operations.hpp"
#include "memory.hpp"
#include "stack.hpp"
#include "opc_bool.hpp"

#include "vm.hpp"

//База хранящая информацию есть ли у опкода аргумент или нет
namespace {
    const std::unordered_map<int, int> COMMAND_ARGS = {
        {PUSH, 1}, {POP, 0}, {ADD, 0}, {SUB, 0}, {MUL, 0}, {DIV, 0},
        {PRINT, 0}, {HALT, 0}, {STORE_GLOBAL, 1}, {LOAD_GLOBAL, 1},
        {ALLOC, 0}, {STORE_MEM, 0}, {LOAD_MEM, 0}, {FREE, 0},
        {JUMP, 1}, {JUMPIZ, 1}, {JUMPINZ, 1}, {LABEL, 1},
        {JUMP_RET, 1}, {JUMPIZ_RET, 1}, {JUMPINZ_RET, 1},
        {DUP, 0}, {SWAP, 0}, {CMP_EQ, 1}, {CMP_NE, 1},
        {CMP_GT, 1}, {CMP_LT, 1}, {AND, 0}, {OR, 0}, {NOT, 0}, {MOD, 0}
    };
}

std::map<int, size_t> VM::createLineToIndexMapping(const std::vector<std::variant<int, std::string>>& program) const  {
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

void VM::analyzeLabels(std::vector<std::variant<int, std::string>>& program) {
    size_t index = 0;
    int current_line = 1;
    int count_labels = 0;
    std::map<int, size_t> lineToIndex = this->createLineToIndexMapping(program);
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
    lineToIndex = this->createLineToIndexMapping(program);
    if (labels.find("start") == labels.end()) {
        pc = 0;
    } else {
        pc = lineToIndex[labels["start"]];
    }
}



void VM::executeArithmeticOperation(int command, std::stack<int>& stack) {
    switch (command) {
        case ADD: add(stack); break;
        case SUB: sub(stack); break;
        case MUL: mul(stack); break;
        case DIV: div(stack); break;
        case MOD: mod(stack); break;
        default:
            throw std::runtime_error("Unknown arithmetic operation: " + std::to_string(command));
    }
}

void VM::executeJumpOperation(int command, std::vector<std::variant<int, std::string>>& program, size_t& pc, const std::map<int, size_t>& lineToIndex, std::stack<int>& stack) {
    switch (command) {
        case JUMP: jump(program, pc, lineToIndex); break;
        case JUMPIZ: jumpiz(program, pc, stack, lineToIndex); break;
        case JUMPINZ: jumpinz(program, pc, stack, lineToIndex); break;
        case JUMP_RET: lastPC.push(pc); jump(program, pc, lineToIndex); break;
        case JUMPIZ_RET: lastPC.push(pc); jumpiz(program, pc, stack, lineToIndex); break;
        case JUMPINZ_RET: lastPC.push(pc); jumpinz(program, pc, stack, lineToIndex); break;
        default:
            throw std::runtime_error("Unknown jump operation: " + std::to_string(command));
    }
}

void VM::executeMemoryOperation(int command, std::vector<std::variant<int, std::string>>& program, size_t& pc, std::stack<int>& stack, std::map<int, std::vector<int>>& memory, int& nextAddress) {
    switch (command) {
        case STORE_GLOBAL: {
            int address = std::get<int>(program[++pc]);
            int value = stack.top(); stack.pop();
            globalsV[address] = value;
            break;
        }
        case LOAD_GLOBAL: {
            int address = std::get<int>(program[++pc]);
            if (globalsV.find(address) == globalsV.end()) {
                throw std::runtime_error("[LOAD GLOBAL] Global variable not found");
            }
            stack.push(globalsV[address]);
            break;
        }
        case ALLOC: alloc(stack, memory, nextAddress); break;
        case STORE_MEM: store_mem(stack, memory); break;
        case LOAD_MEM: load_mem(stack, memory); break;
        case FREE: free(stack, memory); break;
        default:
            throw std::runtime_error("Unknown memory operation: " + std::to_string(command));
    }
}

void VM::executeStackOperation(int command, std::stack<int>& stack) {
    switch (command) {
        case POP: pop(stack); break;
        case DUP: dup(stack); break;
        case SWAP: swap(stack); break;
        case PRINT: {
            if (stack.empty()) {
                throw std::runtime_error("Stack error: stack is empty for PRINT");
            }
            std::cout << stack.top() << std::endl;
            stack.pop();
            break;
        }
        default:
            throw std::runtime_error("Unknown stack operation: " + std::to_string(command));
    }
}

void VM::executeComparisonOperation(int command, std::stack<int>& stack, size_t& pc, std::vector<std::variant<int, std::string>>& program, const std::map<int, size_t>& lineToIndex) {
    switch (command) {
        case CMP_EQ: cmp_eq(stack, pc, program, lineToIndex); break;
        case CMP_NE: cmp_ne(stack, pc, program, lineToIndex); break;
        case CMP_GT: cmp_gt(stack, pc, program, lineToIndex); break;
        case CMP_LT: cmp_lt(stack, pc, program, lineToIndex); break;
        default:
            throw std::runtime_error("Unknown comparison operation: " + std::to_string(command));
    }
}

void VM::executeLogicalOperation(int command, std::stack<int>& stack) {
    switch (command) {
        case AND: _and(stack); break;
        case OR: _or(stack); break;
        case NOT: _not(stack); break;
        default:
            throw std::runtime_error("Unknown logical operation: " + std::to_string(command));
    }
}

void VM::execute(std::vector<std::variant<int, std::string>>& program) {
    this->analyzeLabels(program);
    std::map<int, size_t> lineToIndex = createLineToIndexMapping(program);

    while (pc < program.size()) {
        const auto& instruction = program[pc];

        if (!std::holds_alternative<int>(instruction)) {
            throw std::runtime_error("Expected command but found a string");
        }

        int command = std::get<int>(instruction);

        try {
            switch (command) {
                case PUSH:
                    push(program, pc, stack);
                    break;
                case POP:
                case DUP:
                case SWAP:
                case PRINT:
                    executeStackOperation(command, stack);
                    break;
                case ADD:
                case SUB:
                case MUL:
                case DIV:
                case MOD:
                    executeArithmeticOperation(command, stack);
                    break;
                case STORE_GLOBAL:
                case LOAD_GLOBAL:
                case ALLOC:
                case STORE_MEM:
                case LOAD_MEM:
                case FREE:
                    executeMemoryOperation(command, program, pc, stack, memory, nextAddress);
                    break;
                case JUMP:
                case JUMPIZ:
                case JUMPINZ:
                case JUMP_RET:
                case JUMPIZ_RET:
                case JUMPINZ_RET:
                    executeJumpOperation(command, program, pc, lineToIndex, stack);
                    break;
                case CMP_EQ:
                case CMP_NE:
                case CMP_GT:
                case CMP_LT:
                    executeComparisonOperation(command, stack, pc, program, lineToIndex);
                    break;
                case AND:
                case OR:
                case NOT:
                    executeLogicalOperation(command, stack);
                    break;
                case HALT:
                    return;  // Завершение программы
                case LABEL:
                    pc += 2;  // Пропускаем метку и её аргумент
                    break;
                default:
                    throw std::runtime_error("Unknown command: " + std::to_string(command));
            }
        } catch (const std::exception& e) {
            throw std::runtime_error("Error at line " + std::to_string(pc) + ": " + e.what());
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
