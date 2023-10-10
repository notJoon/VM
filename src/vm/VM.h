/**
 * @file vm.h
 * 
 * @brief Virtual Machine
 */
#ifndef __VM_h
#define __VM_h

#include <string>

#include "../bytecode/OpCode.h"

/**
 * @brief Reads the current byte in  the bytecode
 * and advances the instruction pointer.
 */
#define READ_BYTE() *ip++

class VM {
    public:
        VM() {}

        /**
         * @brief Execute a program
         */
        void execute(const std::string &program) {
            // 1. Parse the program
            // auto program = parser->parse(program);

            // 2, Compile program to bytecode
            // code = compiler->compile(program);

            code = {OP_HALT};

            // Set instruction pointer to the first instruction
            ip = &code[0];

            return eval();
        }

        /**
         * @brief Main eval loop
         */
        void eval() {
            for (;;) {
                switch (READ_BYTE()) {
                    case OP_HALT:
                        return;
                }
            }
        }
        /**
         * @brief Instruction pointer (aka Program Counter)
         */
        uint8_t* ip;

        /**
         * @brief Bytecode
         */
        std::vector<uint8_t> code;
};

#endif