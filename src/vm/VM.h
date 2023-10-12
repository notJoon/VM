// clang++ -std=c++17 -Wall -ggdb3 ./vm.cpp -o ./VM && ./VM   

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

/**
 * @brief Binary Operation
 */
// stack pops in reverse order, So op2 is popped first
#define BINARY_OP(op)                   \
    do {                                \
        auto op2 = AS_NUMBER(pop());    \
        auto op1 = AS_NUMBER(pop());    \
        push(NUMBER(op1 op op2));       \
    } while (false)

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
            constants.push_back(ALLOC_STRING("Hello, "));
            constants.push_back(ALLOC_STRING("World!"));
            code = {OP_CONST, 0, OP_CONST, 1, OP_ADD, OP_HALT};

            // Set instruction pointer to the first instruction
            ip = &code[0];

            // Initialize stack pointer
            sp = &stack[0];

            return eval();
        }

        /**
         * @brief Main eval loop
         */
        Value eval() {
            for (;;) {
                auto opcode = READ_BYTE();
                // log(opcode);
                switch (opcode) {
                    case OP_HALT:
                        return pop();
                    // ------------------------------
                    // Constants
                    case OP_CONST:
                        push(GET_CONST());
                        break;

                    // ------------------------------
                    // Arithmetic Operations
                    case OP_ADD: {
                        auto op2 = pop();
                        auto op1 = pop();

                        // numeric addition
                        if (IS_NUMBER(op1) && IS_NUMBER(op2)) {
                            auto v1 = AS_NUMBER(op1);
                            auto v2 = AS_NUMBER(op2);
                            push(NUMBER(v1 + v2));
                        }

                        // string concatenation
                        else if (IS_STRING(op1) && IS_STRING(op2)) {
                            auto s1 = AS_CPPSTRING(op1);
                            auto s2 = AS_CPPSTRING(op2);
                            push(ALLOC_STRING(s1 + s2));
                        }

                        break;
                    }

                    case OP_SUB: {
                        BINARY_OP(-);
                        break;
                    }

                    case OP_MUL: {
                        BINARY_OP(*);
                        break;
                    }

                    case OP_DIV: {
                        BINARY_OP(/);
                        break;
                    }

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