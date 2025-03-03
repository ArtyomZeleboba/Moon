/* Опкоды команд */
#ifndef OPCODE_IDS_H
#define OPCODE_IDS_H

#define PUSH         0
#define POP          1
#define ADD          2   
#define SUB          3   
#define MUL          4  
#define DIV          5   
#define PRINT        6 
#define HALT         7   
#define STORE_GLOBAL 8
#define LOAD_GLOBAL  9

#define ALLOC        10
#define STORE_MEM    11
#define LOAD_MEM     12
#define FREE         13

#define JUMP         14
#define JUMPIZ       15
#define JUMPINZ      16
#define JUMP_RET     17
#define JUMPIZ_RET   18
#define JUMPINZ_RET  19

#define LABEL        20

#define DUP          21
#define SWAP         22

#define CMP_EQ       23
#define CMP_NE       24
#define CMP_GT       25
#define CMP_LT       26
#define AND          27
#define OR           28
#define NOT          29

#define MOD          30
#define INC          31
#define DEC          32
#define NEG          33
#define ABS          34
#define POW          35
#define SQRT         36
#define MIN          37
#define MAX          38
#define AVG          39
#define RAND         40

#endif // OPCODE_IDS_H
