#pragma once
#include <cstdint>

namespace pit {
	namespace runtime {

		enum Instruction {
			LD_CONST	= 0x0,
			LD_LOCAL	= 0x1,
			ST_LOCAL	= 0x2,
			JMP			= 0x3,
			CALL		= 0x4,
			RET			= 0x5,
			NEW_CONT    = 0x6,
			GET_CONT    = 0x7,
			SET_CONT    = 0x8,
			KGET_CONT   = 0x9,
			KSET_CONT   = 0xA,
			AND,
			OR,
			NOT,
			EQ,
			GT,
			LT,
			GE,
			LE,
			TYPE,
			NATIVE
		};
		
		const uint32_t arg_count_lookup[] = {
			2,
		};

		constexpr uint32_t arg_count(Instruction instruction){
			return arg_count_lookup[instruction];
		}
	}
}