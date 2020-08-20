#pragma once
#include "bundle.hpp"
#include "instruction.hpp"
#include <stack>

#define DEBUG_EXEC_INSTR

/*
this file actually runs the 'cyanide' virtual machine
*/

namespace pit {

	enum ExecutionResult {
		EXEC_OK,
		EXEC_RUNTIME_ERR,
	};

	class VM {
	public:
		VM();
		ExecutionResult run(Bundle bundle);
	private:
		// all inner functions etc live in this one bundle
		Bundle bundle;
		uint8_t*instr_ptr;
		std::stack<Bundle> call_stack;
		inline uint8_t next_instr();
	};
}