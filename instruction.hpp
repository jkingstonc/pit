#pragma once
#include <cstdint>
#include <iostream>


namespace pit {
	
	class Bundle;

	enum Instruction {
		LD_IMM,   // load an immediate integer value e.g. LD_IMM 22
		LD_CONST,
		LD_LOCAL,
		ST_LOCAL,
		JMP,
		CALL,
		RET,
		NEW_CONT,
		GET_CONT,
		SET_CONT,
		KGET_CONT,
		KSET_CONT,
		NEG,
		ADD,
		SUB,
		MUL,
		DIV,
		AND,
		OR,
		NOT,
		EQ,
		GT,
		LT,
		GE,
		LE,
		GETSIG,
		NATIVE
	};
}