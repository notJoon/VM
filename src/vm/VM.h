/**
 * @file vm.h
 * 
 * @brief Virtual Machine
 */
#ifndef VM_h
#define VM_h

#include<array>
#include <string>
#include <iostream>

#include "../bytecode/OpCode.h"
#include "../Logger.h"
#include "../Value.h"
/**
 * @brief Reads the current byte in  the bytecode
 * and advances the instruction pointer.
 */
#define READ_BYTE() *ip++

/**
 * @brief Get the constant at the given index
*/
#define GET_CONST() constants[READ_BYTE()]

/**
 * @brief Stack top (stack overflow after exceeding this limit)
 */
#define STACK_LIMIT 512

class VM {
    public:
        VM() {}

        /**
         * @brief Pushes a value onto the stack
         */
        void push(const Value& value) {
            if ((size_t)(sp - stack.begin()) == STACK_LIMIT) {
                DIE << "Stack overflow";
            }
            *sp = value;
            sp++;
        }

        /**
         * @brief Pop a value from the stack
        */
        Value pop() {
            if (sp == stack.begin()) {
                DIE << "pop(): Stack underflow";
            }
            sp--;
            return *sp;
        }

        /**
         * @brief Execute a program
         */
        Value execute(const std::string& program) {
            // 1. Parse the program
            // auto program = parser->parse(program);

            // 2, Compile program to bytecode
            // code = compiler->compile(program);

            constants.push_back(NUMBER(42));
            code = {OP_CONST, 0, OP_HALT};

            // Set instruction pointer to the first instruction
            ip = &code[0];

            return eval();
        }

        /**
         * @brief Main eval loop
         */
        Value eval() {
            for (;;) {
                auto opcode = READ_BYTE();
                log(opcode);
                switch (opcode) {
                    case OP_HALT:
                        return pop();
                    case OP_CONST:
                        push(GET_CONST());
                        break;
                    default:
                        DIE << "Unknown opcode: " << std::hex << opcode;
                }
            }
        }
        /**
         * @brief Instruction pointer (aka Program Counter)
         */
        uint8_t* ip;

        /**
         * @brief Stack pointer(IP).
        */
        Value* sp;

        /**
         * @brief Operand Stack.
        */
        std::array<Value, STACK_LIMIT> stack;

        /**
         * @brief Constant pool
         */
        std::vector<Value> constants;

        /**
         * @brief Bytecode
         */
        std::vector<uint8_t> code;
};

#endif