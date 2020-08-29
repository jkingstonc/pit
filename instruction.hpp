#pragma once
#include <cstdint>
#include <iostream>


namespace pit {
	
	class Bundle;

	enum Instruction {
		OP_DBG,
		OP_HLT,
		OP_LD_I_IMM,
		OP_LD_B_IMM,
		OP_LD_CONST,
		OP_LD_LOCAL,
		OP_ST_LOCAL,
		OP_JMP,		// jump if true
		OP_CALL,
		OP_YIELD,
		OP_RET,
		OP_NEW_FN,
		OP_NEW_ARR,
		OP_NEW_CONT,
		OP_GET_CONT,
		OP_SET_CONT,
		OP_KGET_CONT,
		OP_KSET_CONT,
		OP_NEG,
		OP_ADD,
		OP_SUB,
		OP_MUL,
		OP_DIV,
		OP_AND,
		OP_OR,
		OP_NOT,
		OP_EQ,
		OP_GT,
		OP_LT,
		OP_GE,
		OP_LE,
		OP_GETSIG,
		OP_NATIVE
	};
}