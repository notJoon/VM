/**
 * @file opcode.h
 * @brief Instruction Set for VM
 * 
 */

#ifndef OpCode_h
#define OpCode_h

/**
 * @brief Stop the program.
 */
#define OP_HALT 0x00

/**
 * @brief Push constant to stack.
 */
#define OP_CONST 0x01

/**
 * @brief  Add instruction
 */
#define OP_ADD 0x02
#define OP_SUB 0x03
#define OP_MUL 0x04
#define OP_DIV 0x05

#endif